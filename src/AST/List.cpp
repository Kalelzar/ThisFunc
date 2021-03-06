#include <ThisFunc/AST.hpp>
#include <ThisFunc/ExtendedAST.hpp>
#include <cmath>
#include <iostream>

namespace ThisFunc::AST {

void List::print (std::ostream* out) {
  *out << "(list ";
  for (auto& element : values) {
    if (element != values.front ( )) *out << " ";
    element->print (out);
  }
  *out << ")";
}

ElementPtr List::optimal ( ) {
  std::list<ExpressionPtr> newValues;
  for (auto& element : values) {
    newValues.push_back (ptr_cast<Expression> (element->optimal ( )));
  }

  return std::make_shared<List> (std::move (newValues), line, column);
}

void List::compile (VM::Chunk* chunk, Resolver& resolver) {
  for (auto& element : values) { element->compile (chunk, resolver); }
  chunk->write (VM::OP_LIST, {line, column});
  chunk->write (values.size ( ), {line, column});
}

}     // namespace ThisFunc::AST
