#include <ThisFunc/AST.hpp>
#include <ThisFunc/TypeDeduction.hpp>
#include <iostream>

namespace ThisFunc::AST {

void Identifier::print (std::ostream* out) {
  if (identifier.starts_with ("#")) {
    *out << "_" << (identifier.c_str ( ) + 1);
  } else {
    *out << identifier;
  }
}

ElementPtr Identifier::optimal ( ) {
  return std::make_shared<Identifier> (*this);
}

void Identifier::compile (VM::Chunk* chunk, Resolver& resolver) {
  if (identifier.starts_with ("#")) {
    u32 i;
    sscanf (identifier.c_str ( ), "#%d", &i);
    chunk->write (VM::OP_LOAD, {line, column});
    chunk->write (i, {line, column});
  } else {
    auto r = resolver.get (identifier);
    chunk->write (r->index, {line, column});
  }
}

}     // namespace ThisFunc::AST
