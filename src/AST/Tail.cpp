#include "ThisFunc/AST.hpp"
#include <ThisFunc/ExtendedAST.hpp>

#include <iostream>
#include <cmath>

namespace ThisFunc::AST {

void Tail::print() {
  std::cout << "(tail ";
  value->print();
  std::cout << ")";
}

ElementPtr Tail::optimal() {
  value->values.pop_front();
  return value;
}

} // namespace ThisFunc::AST
