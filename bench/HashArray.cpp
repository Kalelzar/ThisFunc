#include <Kal/HashArray.hpp>
#include <cassert>
#include <hayai/hayai.hpp>

class IntHashArrayFixture : public ::hayai::Fixture {
  public:
  virtual void SetUp ( ) {
    this->array = new HashArray<int> ( );
    array->push (0);
  }

  virtual void    TearDown ( ) { delete this->array; }

  HashArray<int>* array;
};

struct Fancy {
  int a = 0;
  int b = 1;
  int c = 2;

  u32 hashCode ( ) const {
    u32 ah   = FNV_1A<int>::hash (&a);
    u32 bah  = FNV_1A<int>::hash (&b, ah);
    u32 cbah = FNV_1A<int>::hash (&c, bah);
    return cbah;
  }

  bool operator== (const Fancy& other) const {
    return a == other.a && b == other.b && c == other.c;
  }
};

struct Huge {
  u64 data[256];

  u32 hashCode ( ) const {
    u32 hash = FNV_1A<u64>::hash (&data[0]);
    for (u32 i = 1; i < 256; i++) { hash = FNV_1A<u64>::hash (&data[0]); }
    return hash;
  }

  bool operator== (const Huge& other) const {
    for (u32 i = 0; i < 256; i++)
      if (data[i] != other.data[i]) return false;
    return true;
  }
};

class FancyHashArrayFixture : public ::hayai::Fixture {
  public:
  virtual void SetUp ( ) {
    this->array = new HashArray<Fancy, HashCode<Fancy>> ( );
    array->push ({0, 1, 2});
  }

  virtual void                       TearDown ( ) { delete this->array; }

  HashArray<Fancy, HashCode<Fancy>>* array;
};

class HugeHashArrayFixture : public ::hayai::Fixture {
  public:
  virtual void SetUp ( ) {
    this->array = new HashArray<Huge, HashCode<Huge>> ( );
    array->push ({{}});
  }

  virtual void                     TearDown ( ) { delete this->array; }

  HashArray<Huge, HashCode<Huge>>* array;
};

class FancyPtrHashArrayFixture : public ::hayai::Fixture {
  public:
  virtual void SetUp ( ) {
    this->array = new HashArray<Fancy*, HashCode<Fancy*>> ( );
    i           = new Fancy{1, 2, 3};
    array->push (i);
  }

  virtual void TearDown ( ) {
    delete i;
    delete this->array;
  }

  HashArray<Fancy*, HashCode<Fancy*>>* array;
  Fancy*                               i;
};

BENCHMARK_F (IntHashArrayFixture, AddElement, 10, 100) {
  array->push (rand ( ));
}
BENCHMARK_F (IntHashArrayFixture, ContainsElement, 10, 100) {
  array->contains (0);
}
BENCHMARK_F (IntHashArrayFixture, RemoveElement, 10, 100) {
  auto i = array->push (0);
  array->pop (i);
  assert (!array->contains (0));
}


BENCHMARK_F (FancyHashArrayFixture, AddElement, 10, 100) {
  array->push ({0, 1, 2});
}
BENCHMARK_F (FancyHashArrayFixture, ContainsElement, 10, 100) {
  array->contains ({0, 1, 2});
}

BENCHMARK_F (HugeHashArrayFixture, AddElement, 10, 100) { array->push ({{}}); }
BENCHMARK_F (HugeHashArrayFixture, ContainsElement, 10, 100) {
  array->contains ({{}});
}

BENCHMARK_F (FancyPtrHashArrayFixture, AddElement, 10, 100) { array->push (i); }
BENCHMARK_F (FancyPtrHashArrayFixture, ContainsElement, 10, 100) {
  array->contains (i);
}
