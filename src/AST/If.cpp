#include "ThisFunc/AST.hpp"
#include <ThisFunc/ExtendedAST.hpp>

#include <iostream>
#include <cmath>

namespace ThisFunc::AST {

void If::print() {
  std::cout << "(if ";
  cond->print();
  std::cout << " ";
  ifTrue->print();
  std::cout << " ";
  ifFalse->print();
  std::cout << ")";
}

ElementPtr If::optimal() {
  ElementPtr newCond = cond->optimal();

  if (cond->isNumber()) {
    double eval = ptr_cast<Number>(cond)->number;
    if(std::fabs(eval) <= 1E-6) {
      return ifFalse->optimal();
    }else{
      return ifTrue->optimal();
    }
  }

  return std::make_shared<If>(ptr_cast<Expression>(newCond),
                              ptr_cast<Expression>(ifTrue->optimal()),
                              ptr_cast<Expression>(ifFalse->optimal()));
}

void If::compile(VM::Chunk *chunk) { chunk->write(VM::NOOP, {0, 0}); }

} // namespace ThisFunc::AST
