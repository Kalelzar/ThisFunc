#include "ThisFunc/AST.hpp"
#include <ThisFunc/ExtendedAST.hpp>

#include <iostream>
#include <cmath>

namespace ThisFunc::AST {

void Cos::print() {
  std::cout << "(cos ";
  value->print();
  std::cout << ")";
}

/**
 * @copydoc Element::optimal
 * @details An optimal Cos is one which:
              <br>1) if it's argument optimizes to a Number: A Number
containing the cosine of the argument
              <br>2) otherwise: a Cos with an optimal argument
 */
ElementPtr Cos::optimal() {
  ElementPtr val = value->optimal();

  if (value->isNumber()) {
    double num = ptr_cast<Number>(val)->number;
    return std::make_shared<Number>(std::cos(num));
  }
  return std::make_shared<Cos>(ptr_cast<Expression>(val));
}

} // namespace ThisFunc::AST
