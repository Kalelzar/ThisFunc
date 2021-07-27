#include "ThisFunc/AST.hpp"
#include <ThisFunc/ExtendedAST.hpp>

#include <cmath>
#include <iostream>

namespace ThisFunc::AST {

void Sin::print() {
  std::cout << "(sin ";
  value->print();
  std::cout << ")";
}

/**
 * @copydoc Element::optimal
 * @details An optimal Sin is one which:
 <br>1) if it's argument optimizes to a Number: A Number
 containing the sine of the argument
 <br>2) otherwise: a Sin with an optimal argument
*/
ElementPtr Sin::optimal() {
  ElementPtr val = value->optimal();

  if (value->isNumber()) {
    double num = ptr_cast<Number>(val)->number;
    return std::make_shared<Number>(std::sin(num));
  }
  return std::make_shared<Sin>(ptr_cast<Expression>(val));
}

void Sin::compile(VM::Chunk *chunk) { chunk->write(VM::NOOP, {0, 0}); }

} // namespace ThisFunc::AST
