#include <ThisFunc/AST.hpp>
#include <ThisFunc/ExtendedAST.hpp>
#include <cmath>
#include <iostream>

namespace ThisFunc::AST {

void Sqrt::print (std::ostream* out) {
  *out << "(sqrt ";
  value->print (out);
  *out << ")";
}

ElementPtr Sqrt::optimal ( ) {
  ElementPtr val = value->optimal ( );

  if (value->isNumber ( )) {
    double num = ptr_cast<Number> (val)->number;
    return std::make_shared<Number> (std::sqrt (num), line, column);
  }
  return std::make_shared<Sqrt> (ptr_cast<Expression> (val), line, column);
}

void Sqrt::compile (VM::Chunk* chunk) {
  chunk->write (VM::NOOP, {line, column});
}

}     // namespace ThisFunc::AST
