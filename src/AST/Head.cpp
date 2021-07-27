#include "ThisFunc/AST.hpp"
#include <ThisFunc/ExtendedAST.hpp>

#include <iostream>
#include <cmath>
#include <memory>

namespace ThisFunc::AST {

void Head::print() {
  std::cout << "(head ";
  value->print();
  std::cout << ")";
}

ElementPtr Head::optimal() {
  if(value->values.size() >= 1)
    return value->values.front()->optimal();
  else return std::make_shared<List>(std::list<ExpressionPtr>());
}

void Head::compile(VM::Chunk *chunk) { chunk->write(VM::NOOP, {0, 0}); }

} // namespace ThisFunc::AST
