#include "ThisFunc/AST.hpp"
#include <ThisFunc/ExtendedAST.hpp>

#include <iostream>
#include <cmath>

namespace ThisFunc::AST {

void Add::print() {
  std::cout << "(+ ";
  lhs->print();
  std::cout << " ";
  rhs->print();
  std::cout << ")";
}

ElementPtr Add::optimal() {
  ElementPtr nlhs = lhs->optimal();
  ElementPtr nrhs = rhs->optimal();

  if (nlhs->isNumber() && nrhs->isNumber()) {
    double lhsd = ptr_cast<Number>(nlhs)->number;
    double rhsd = ptr_cast<Number>(nrhs)->number;
    return std::make_shared<Number>(lhsd + rhsd);
  }
  return std::make_shared<Add>(ptr_cast<Expression>(nlhs),
                               ptr_cast<Expression>(nrhs));
}

} // namespace ThisFunc::AST
