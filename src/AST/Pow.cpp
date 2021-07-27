#include "ThisFunc/AST.hpp"
#include <ThisFunc/ExtendedAST.hpp>

#include <iostream>
#include <cmath>

namespace ThisFunc::AST {

void Pow::print() {
  std::cout << "(^ ";
  lhs->print();
  std::cout << " ";
  rhs->print();
  std::cout << ")";
}

ElementPtr Pow::optimal() {
  ElementPtr nlhs = lhs->optimal();
  ElementPtr nrhs = rhs->optimal();

  if (nlhs->isNumber() && nrhs->isNumber()) {
    double lhsd = ptr_cast<Number>(nlhs)->number;
    double rhsd = ptr_cast<Number>(nrhs)->number;
    return std::make_shared<Number>(std::pow(lhsd, rhsd));
  }
  return std::make_shared<Pow>(ptr_cast<Expression>(nlhs),
                               ptr_cast<Expression>(nrhs));
}

void Pow::compile(VM::Chunk *chunk) { chunk->write(VM::NOOP, {0, 0}); }

} // namespace ThisFunc::AST
