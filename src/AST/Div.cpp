#include "ThisFunc/AST.hpp"
#include <ThisFunc/ExtendedAST.hpp>

#include <iostream>
#include <cmath>

namespace ThisFunc::AST {

void Div::print() {
  std::cout << "(/ ";
  lhs->print();
  std::cout << " ";
  rhs->print();
  std::cout << ")";
}

ElementPtr Div::optimal() {
  ElementPtr nlhs = lhs->optimal();
  ElementPtr nrhs = rhs->optimal();

  if (nlhs->isNumber() && nrhs->isNumber()) {
    double lhsd = ptr_cast<Number>(nlhs)->number;
    double rhsd = ptr_cast<Number>(nrhs)->number;
    if(std::fabs(rhsd) <= 1E-6) throw 0;
    return std::make_shared<Number>(lhsd / rhsd);
  }
  return std::make_shared<Div>(ptr_cast<Expression>(nlhs),
                               ptr_cast<Expression>(nrhs));
}

} // namespace ThisFunc::AST
