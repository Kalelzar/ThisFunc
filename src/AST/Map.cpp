#include <ThisFunc/AST.hpp>
#include <ThisFunc/ExtendedAST.hpp>
#include <cmath>
#include <iostream>
#include <memory>

namespace ThisFunc::AST {

void Map::print (std::ostream* out) {
  *out << "(mapcar #'";
  funname->print (out);
  *out << " ";
  list->print (out);
  *out << ")";
}

ElementPtr Map::optimal ( ) {
  IdentifierPtr nfunname = ptr_cast<Identifier> (funname->optimal ( ));
  ListPtr       nlist    = ptr_cast<List> (list->optimal ( ));

  std::list<ExpressionPtr> mapped;

  for (auto& element : nlist->values) {
    std::list<ExpressionPtr> args;
    args.push_back (element);
    mapped.push_back (ptr_cast<Expression> (
      std::make_shared<Funcall> (nfunname, std::move (args), line, column)));
  }

  return make_shared<List> (std::move (mapped), line, column)->optimal ( );
}

void Map::compile (VM::Chunk* chunk, Resolver& resolver) {
  list->compile (chunk, resolver);
  funname->compile (chunk, resolver);
  chunk->write (VM::OP_MAP, {line, column});
}

}     // namespace ThisFunc::AST
