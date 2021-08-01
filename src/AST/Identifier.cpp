#include <ThisFunc/AST.hpp>
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

void Identifier::compile (VM::Chunk* chunk) {
  chunk->write (VM::NOOP, {line, column});
}

}     // namespace ThisFunc::AST
