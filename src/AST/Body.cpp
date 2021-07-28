#include <ThisFunc/AST.hpp>
#include <ThisFunc/Chunk.hpp>
#include <iostream>

namespace ThisFunc::AST {

void Body::print ( ) {
  for (auto& s : statements) {
    s->print ( );
    std::cout << std::endl;
  }
}

void Body::compile (VM::Chunk* chunk) {
  for (auto& statement : statements) {
    statement->compile (chunk);
    chunk->write (VM::OP_PRINT, {statement->line, statement->column});
  }
  chunk->write (VM::OP_RETURN, {line, column});
}

/**
 * @copydoc Element::optimal
 * @details An optimal Body is one whose Statements are optimal.
 */
ElementPtr Body::optimal ( ) {
  std::list<StatementPtr> newStatements;
  for (auto& statement : statements) {
    newStatements.push_back (ptr_cast<Statement> (statement->optimal ( )));
  }
  return make_shared<Body> (std::move (newStatements), line, column);
}

}     // namespace ThisFunc::AST
