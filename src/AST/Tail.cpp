#include <ThisFunc/AST.hpp>
#include <ThisFunc/ExtendedAST.hpp>
#include <cmath>
#include <iostream>

namespace ThisFunc::AST {

void Tail::print ( ) {
  std::cout << "(tail ";
  value->print ( );
  std::cout << ")";
}

ElementPtr Tail::optimal ( ) {
  value->values.pop_front ( );
  return value;
}

void Tail::compile (VM::Chunk* chunk) {
  chunk->write (VM::NOOP, {line, column});
}

}     // namespace ThisFunc::AST
