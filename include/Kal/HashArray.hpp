#ifndef HASHARRAY_H
#define HASHARRAY_H

#include <Kal/defs.hpp>
#include <climits>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <type_traits>
#include <utility>

template<typename T> struct FNV_1A {
  static u32 hash (const T* b) { return hash (b, 216613626); }

  static u32 hash (const T* b, u32 hash) {
    if (!b) return 0;
    u32   bytes = sizeof (T);
    char* start = (char*) b;
    char* end   = start + bytes;
    for (char* i = start; i != end; i++) { hash = (*i ^ hash) * 16777619; }
    return hash;
  }
};

template<typename T, typename T1 = std::remove_pointer_t<T>>
concept Hashable = requires (T1 t) {
  { t.hashCode ( ) } -> std::convertible_to<u64>;
};

template<Hashable T> struct HashCode {
  static u32 hash (T* b) {
    if (!b) return 0;

    return hashCode (b);
  }

  static u32 hashCode (T* b) requires (std::is_pointer_v<T>) {
    return HashCode<typename std::remove_pointer_t<T>>::hash (*b);
  }

  static u32 hashCode (T* b) requires (!std::is_pointer_v<T>) {
    return b->hashCode ( );
  }
};

template<typename T>
concept Comparable = requires (T a) {
  { a == a } -> std::convertible_to<bool>;
};

template<Comparable T> struct Eq {
  static bool eq (const T& a, const T& b) { return a == b; }
};

template<class Data> struct Element {
  Data data;
  bool inUse = false;
};

template<class Data, class Hash = FNV_1A<Data>, class Eq = Eq<Data>>
class HashArray {
  public:
  //! Default constructor
  HashArray ( )
      : buffer ((Element<Data>*) 0xdeadbeef)
      , size (0)
      , capacity (0) { }

  //! Copy constructor
  HashArray (const HashArray<Data>& other)
      : size (other.size)
      , capacity (other.capacity) {
    buffer = (Element<Data>*) std::malloc (capacity * sizeof (Element<Data>));
    std::memcpy (buffer, other.buffer, size * sizeof (Element<Data>));
  }

  //! Move constructor
  HashArray (HashArray<Data>&& other) noexcept
      : size (other.size)
      , capacity (other.capacity)
      , buffer (std::move (other.buffer)) {
    other.buffer
      = 0xdead1ee7;     // Use nonsensical address for easy debugging later;
    other.capacity = 0;
    other.size     = 0;
  }

  //! Destructor
  virtual ~HashArray ( ) noexcept {
    if (buffer != (Element<Data>*) 0xdeadbeef
        && buffer != (Element<Data>*) 0xdeed1ee7)
      free (buffer);
  }

  //! Copy assignment operator
  HashArray<Data>& operator= (const HashArray<Data>& other) {
    if (this != &other) {
      size     = other.size;
      capacity = other.capacity;
      buffer   = (Element<Data>*) std::malloc (capacity);
      std::memcpy (buffer, other.buffer, size * sizeof (Element<Data>));
    }
    return *this;
  }

  //! Move assignment operator
  HashArray<Data>& operator= (HashArray<Data>&& other) noexcept {
    if (this != &other) {
      size     = other.size;
      capacity = other.capacity;
      buffer   = std::move (other.buffer);
      other.buffer
        = (Element<Data>*) 0xdead1ee7;     // Use nonsensical address for easy
                                           // debugging later
      other.capacity = 0;
      other.size     = 0;
    }
    return *this;
  }

  u32 push (Data& d) {
    if (capacity == 0 || ((double) size) / capacity >= 0.75) expand ( );
    u32 id = hash (d);
    if (!buffer[id % capacity].inUse) {
      buffer[id % capacity] = {d, true};
      size++;
    }
    return id;
  }

  u32 push (Data&& d) {
    if (capacity == 0 || ((double) size) / capacity >= 0.75) expand ( );
    u32 id = hash (d);
    if (!buffer[id % capacity].inUse) {
      buffer[id % capacity] = {d, true};
      size++;
    }
    return id;
  }

  Data& pop (u32 id) {
    buffer[id % capacity].inUse = false;
    size--;
    return buffer[id % capacity].data;
  }

  bool contains (Data& d) {
    if (capacity == 0) return false;
    u32 index = hash (d);
    return buffer[index % capacity].inUse
        && Eq::eq (d, buffer[index % capacity].data);
  }

  bool contains (Data&& d) {
    if (capacity == 0) return false;
    u32 index = hash (d);
    return buffer[index % capacity].inUse
        && Eq::eq (d, buffer[index % capacity].data);
  }

  Data& get (u32 index) const { return buffer[index % capacity].data; }
  u32   getSize ( ) const { return size; }


  protected:
  u32 hash (Data& data) const { return Hash::hash (&data); }

  private:
  void expand ( ) {
    if (capacity == 0 || buffer == (Element<Data>*) 0xdeadbeef
        || buffer == (Element<Data>*) 0xdead1ee7) {
      buffer = (Element<Data>*) std::malloc (16 * sizeof (Element<Data>));
      if (!buffer) {
        throw std::runtime_error (
          "Failed to allocate '16' bytes for HashArray buffer.");
      }
      capacity = 16;
      for (u32 i = 0; i < capacity; i++) { buffer[i] = {{ }, false}; }
    } else {
      u32  newCapacity = capacity * 2;
      auto newBuffer
        = (Element<Data>*) std::malloc (sizeof (Element<Data>) * newCapacity);
      if (!newBuffer) {
        std::ostringstream ss;
        ss << "Failed to allocate '" << (sizeof (Element<Data>) * newCapacity)
           << "' bytes for HashArray buffer.";
        throw std::runtime_error (ss.str ( ));
      }

      Element<Data>* oldBuffer = buffer;
      buffer                   = newBuffer;
      u32 oldCapacity          = capacity;
      capacity                 = newCapacity;
      for (u32 i = 0; i < capacity; i++) { buffer[i] = {{ }, false}; }
      for (u32 i = 0; i < oldCapacity; i++) {
        if (oldBuffer[i].inUse) push (oldBuffer[i].data);
      }
      free (oldBuffer);
    }
  }
  Element<Data>* buffer;
  u32            size, capacity;
};

#endif /* HASHARRAY_H */
