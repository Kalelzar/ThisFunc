#include <ThisFunc/AST.hpp>
#include <ThisFunc/ExtendedAST.hpp>
#include <cmath>
#include <iostream>

namespace ThisFunc::AST {

void Sin::print (std::ostream* out) {
  *out << "(sin ";
  value->print (out);
  *out << ")";
}

/**
 * @copydoc Element::optimal
 * @details An optimal Sin is one which:
 <br>1) if it's argument optimizes to a Number: A Number
 contaouting the sine of the argument
 <br>2) otherwise: a Sin with an optimal argument
*/
ElementPtr Sin::optimal ( ) {
  ElementPtr val = value->optimal ( );

  if (value->isNumber ( )) {
    double num = ptr_cast<Number> (val)->number;
    return std::make_shared<Number> (std::sin (num), line, column);
  }
  return std::make_shared<Sin> (ptr_cast<Expression> (val), line, column);
}

void Sin::compile (VM::Chunk* chunk) {
  chunk->write (VM::NOOP, {line, column});
}

}     // namespace ThisFunc::AST
