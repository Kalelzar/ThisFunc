#include "ThisFunc/AST.hpp"
#include <ThisFunc/ExtendedAST.hpp>

#include <cmath>
#include <iostream>
#include <memory>

namespace ThisFunc::AST {

void Map::print() {
  std::cout << "(map ";
  funname->print();
  std::cout << " ";
  list->print();
  std::cout << ")";
}

ElementPtr Map::optimal() {
  IdentifierPtr nfunname = ptr_cast<Identifier>(funname->optimal());
  ListPtr nlist = ptr_cast<List>(list->optimal());

  std::list<ExpressionPtr> mapped;

  for (auto &element : nlist->values) {
    std::list<ExpressionPtr> args;
    args.push_back(element);
    mapped.push_back(ptr_cast<Expression>(
        std::make_shared<Funcall>(nfunname, std::move(args))));
  }

  return make_shared<List>(std::move(mapped))->optimal();
}

void Map::compile(VM::Chunk *chunk) { chunk->write(VM::NOOP, {0, 0}); }

} // namespace ThisFunc::AST
