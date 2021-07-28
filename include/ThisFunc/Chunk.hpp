#ifndef CHUNK_H
#define CHUNK_H

#include <Kal/defs.hpp>
#include <ThisFunc/Constant.hpp>
#include <ThisFunc/DynArray.hpp>

namespace ThisFunc::VM {

enum OpCode {
  NOOP,
  OP_PRINT,
  OP_CONSTANT,
  OP_RETURN,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
};

struct CodeLocation {
  u32 line;
  u32 column;
};

class Chunk : public DynArray<Byte> {
  public:
  explicit Chunk ( ) {
    locations = DynArray<CodeLocation> ( );
    constants = DynArray<Constant> ( );
  };

  Constant getConstant (u32 address) const { return constants[address]; }
  u32      addConstant (Constant c) { return constants.write (c); }

  u32      write (Byte next, CodeLocation location) {
    locations.write (location);
    return write (next);
  }

  const CodeLocation operator( ) (u32 index) const { return locations[index]; }

  CodeLocation       operator( ) (u32 index) { return locations[index]; }

  protected:
  using DynArray<Byte>::write;

  private:
  DynArray<CodeLocation> locations;
  DynArray<Constant>     constants;
};

}     // namespace ThisFunc::VM

#endif /* CHUNK_H */
