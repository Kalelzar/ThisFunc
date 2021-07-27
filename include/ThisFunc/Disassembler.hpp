#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <ThisFunc/Chunk.hpp>

#include <string>

namespace ThisFunc::VM {

  void disassemble(const Chunk&);
  u32 instruction(const Chunk&, u32);
  u32 simple(const std::string&, u32);
  u32 constant(const std::string&, const Chunk&, u32);
  void value(Constant);

}


#endif /* DISASSEMBLER_H */
