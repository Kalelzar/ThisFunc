#ifndef CHUNK_H
#define CHUNK_H

#include <Kal/defs.hpp>
#include <ThisFunc/CodeLocation.hpp>
#include <ThisFunc/Constant.hpp>
#include <ThisFunc/DynArray.hpp>
#include <iterator>
#include <vector>

namespace ThisFunc::VM {

enum OpCode {
  NOOP,                 //!
  OP_PRINT,             //!
  OP_CONSTANT,          //!
  OP_RETURN,            //!
  OP_ADD,               //!
  OP_BIND_NUMBER,       //!
  OP_BIND_LIST,         //!
  OP_BIND_FUNCTION,     //!
  OP_LOAD,              //!
  OP_SUBTRACT,          //!
  OP_MULTIPLY,          //!
  OP_DIVIDE,            //!
  OP_SIN,               //!
  OP_LIST,              //!
  OP_MAP,               //!
  OP_FILTER,            //!
  OP_JZ,                //!
  OP_JMP,               //!
  OP_POP,               //!
  OP_POW,               //!
  OP_LE,                //!
  OP_HEAD,
  OP_SQRT,     //!
  OP_COS,      //!
  OP_EQ,       //!
  OP_NAND,     //!
  OP_TAIL,
  OP_CALL,     //!
};

class Chunk {
  public:
  explicit Chunk ( ) {
    locations = std::vector<CodeLocation> ( );
    constants = std::vector<Constant> ( );
    storage   = std::vector<Byte> ( );
  };

  Constant getConstant (const u32 address) const { return constants[address]; }
  u32      addConstant (Constant c) {
    constants.push_back (c);
    return constants.size ( ) - 1;
  }

  u32 getSize ( ) const { return storage.size ( ); }

  u64 address ( ) const { return (u64) this; }

  u32 write (Byte next, CodeLocation location) {
    locations.push_back (location);
    storage.push_back (next);
    return storage.size ( ) - 1;
  }

  const CodeLocation operator( ) (u32 index) const { return locations[index]; }

  CodeLocation       operator( ) (u32 index) { return locations[index]; }
  Byte               operator[] (u32 index) { return storage[index]; }
  const Byte         operator[] (u32 index) const { return storage[index]; }
  Byte               get (u32 index) const { return storage[index]; }

  std::vector<Byte>  getStorage ( ) { return storage; }

  std::vector<Byte>  storage;

  protected:
  private:
  std::vector<CodeLocation> locations;
  std::vector<Constant>     constants;
};

}     // namespace ThisFunc::VM

#endif /* CHUNK_H */
