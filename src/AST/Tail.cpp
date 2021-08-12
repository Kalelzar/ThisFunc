#include <ThisFunc/AST.hpp>
#include <ThisFunc/ExtendedAST.hpp>
#include <cmath>
#include <iostream>

namespace ThisFunc::AST {

void Tail::print (std::ostream* out) {
  *out << "(cdr ";
  value->print (out);
  *out << ")";
}

ElementPtr Tail::optimal ( ) {
  value->values.pop_front ( );
  return value;
}

void Tail::compile (VM::Chunk* chunk, Resolver& resolver) {
  chunk->write (VM::OP_TAIL, {line, column});
}

}     // namespace ThisFunc::AST
