#include <ThisFunc/AST.hpp>
#include <ThisFunc/ExtendedAST.hpp>
#include <cmath>
#include <iostream>

namespace ThisFunc::AST {

void List::print ( ) {
  std::cout << "'(";
  for (auto& element : values) {
    if (element != values.front ( )) std::cout << " ";
    element->print ( );
  }
  std::cout << ")";
}

ElementPtr List::optimal ( ) {
  std::list<ExpressionPtr> newValues;
  for (auto& element : values) {
    newValues.push_back (ptr_cast<Expression> (element->optimal ( )));
  }

  return std::make_shared<List> (std::move (newValues), line, column);
}

void List::compile (VM::Chunk* chunk) {
  chunk->write (VM::NOOP, {line, column});
}

}     // namespace ThisFunc::AST
