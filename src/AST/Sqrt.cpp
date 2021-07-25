#include "ThisFunc/AST.hpp"
#include <ThisFunc/ExtendedAST.hpp>

#include <iostream>
#include <cmath>

namespace ThisFunc::AST {

void Sqrt::print() {
  std::cout << "(√ ";
  value->print();
  std::cout << ")";
}

ElementPtr Sqrt::optimal() {
  ElementPtr val = value->optimal();

  if (value->isNumber()) {
    double num = ptr_cast<Number>(val)->number;
    return std::make_shared<Number>(std::sqrt(num));
  }
  return std::make_shared<Sqrt>(ptr_cast<Expression>(val));
}

} // namespace ThisFunc::AST
