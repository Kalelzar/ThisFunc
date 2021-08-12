#ifndef DYNARRAY_H
#define DYNARRAY_H

#include <Kal/defs.hpp>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <iostream>
#include <stdexcept>

#ifndef THISFUNC_DEFAULT_CHUNKSIZE
#  define THISFUNC_DEFAULT_CHUNKSIZE 8
#endif

namespace ThisFunc {

template<typename Data> class DynArray {
  public:
  //! Default constructor
  DynArray ( ) : capacity (0), size (0), storage ((Data*) 0xdeadbeef) { }

  //! Copy constructor
  DynArray (const DynArray<Data>& other) : storage ((Data*) 0xdeadbeef) {
    copy (other);
  }

  //! Move constructor
  DynArray (DynArray<Data>&& other) noexcept { move (std::move (other)); }

  //! Destructor
  virtual ~DynArray ( ) noexcept {
    std::cerr << "Destroy" << getStorage ( ) << std::endl;
    if (storage && storage != (Data*) 0xdeadbeef) free (storage);
  }

  //! Copy assignment operator
  DynArray& operator= (const DynArray& other) { return copy (other); }

  //! Move assignment operator
  DynArray& operator= (DynArray&& other) noexcept {
    return move (std::move (other));
  }

  u32   getSize ( ) const { return size; }

  u32   getCapacity ( ) const { return size; }

  u64   address ( ) const { return (u64) storage; }

  Data& operator[] (u32 index) {
    if (capacity == 0) {
      throw std::runtime_error ("Accessing uninitialized memory.");
    }
    if (index >= size) return storage[size - 1];
    return storage[index];
  }

  const Data& operator[] (u32 index) const {
    if (capacity == 0) {
      throw std::runtime_error ("Accessing uninitialized memory.");
    }
    if (index >= size) return storage[size - 1];
    return storage[index];
  }

  u32 write (Data& next) {
    if (capacity < size + 1) expand ( );
    storage[size] = next;
    return size++;
  }

  u32 write (Data&& next) {
    if (capacity < size + 1) expand ( );
    storage[size] = std::move (next);
    return size++;
  }

  Data* getStorage ( ) { return storage; }

  protected:
  void expand ( ) {
    u32 newCapacity = capacity ? capacity * 2 : THISFUNC_DEFAULT_CHUNKSIZE;
    if (storage == (Data*) 0xdeadbeef)
      storage = static_cast<Data*> (malloc (sizeof (Data) * newCapacity));
    else
      storage
        = static_cast<Data*> (realloc (storage, sizeof (Data) * newCapacity));

    if (storage == nullptr) {
      // Failed to allocate memory for the storage buffer
      // There is nothing we can do.
      std::cerr << "FATAL ERROR: Failed to allocate storage chunk of size "
                << newCapacity << ". Aborting.";
      exit (63);
    }
    capacity = newCapacity;
  }

  DynArray<Data>& copy (const DynArray<Data>& other) {
    if (&other != this) {
      if (storage == (Data*) 0xdeadbeef) {
        storage = (Data*) malloc (other.capacity * sizeof (Data));
      }
      storage
        = static_cast<Data*> (memcpy (storage, other.storage, other.capacity));
      capacity = other.capacity;
      size     = other.size;
    }
    return *this;
  }

  DynArray<Data>& move (DynArray<Data>&& other) {
    if (&other != this) {
      storage        = other.storage;
      other.storage  = nullptr;
      capacity       = other.capacity;
      size           = other.size;
      other.capacity = 0;
      other.size     = 0;
    }
    return *this;
  }

  private:
  Data* storage;
  u32   capacity, size;
};
}     // namespace ThisFunc

#endif /* DYNARRAY_H */
