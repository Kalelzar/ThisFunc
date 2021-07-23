#include "ThisFunc/AST.hpp"
#include <ThisFunc/ExtendedAST.hpp>

#include <iostream>

namespace ThisFunc::AST {

void Sub::print() {
  std::cout << "(- ";
  lhs->print();
  std::cout << " ";
  rhs->print();
  std::cout << ")";
}

ElementPtr Sub::optimal() {
  ElementPtr nlhs = lhs->optimal();
  ElementPtr nrhs = rhs->optimal();

  if (nlhs->isNumber() && nrhs->isNumber()) {
    return std::make_shared<Number>(ptr_cast<Number>(nlhs)->number -
                                    ptr_cast<Number>(nrhs)->number);
  }
  return std::make_shared<Sub>(ptr_cast<Expression>(nlhs),
                               ptr_cast<Expression>(nrhs));
}

} // namespace ThisFunc::AST
