#include <ThisFunc/AST.hpp>
#include <ThisFunc/Chunk.hpp>
#include <ThisFunc/ExtendedAST.hpp>
#include <iostream>

namespace ThisFunc::AST {

void Sub::print (std::ostream* out) {
  *out << "(- ";
  lhs->print (out);
  *out << " ";
  rhs->print (out);
  *out << ")";
}

ElementPtr Sub::optimal ( ) {
  ElementPtr nlhs = lhs->optimal ( );
  ElementPtr nrhs = rhs->optimal ( );

  if (nlhs->isNumber ( ) && nrhs->isNumber ( )) {
    return std::make_shared<Number> (ptr_cast<Number> (nlhs)->number
                                       - ptr_cast<Number> (nrhs)->number,
                                     line,
                                     column);
  }
  return std::make_shared<Sub> (ptr_cast<Expression> (nlhs),
                                ptr_cast<Expression> (nrhs),
                                line,
                                column);
}

void Sub::compile (VM::Chunk* chunk) {
  lhs->compile (chunk);
  rhs->compile (chunk);
  chunk->write (VM::OP_SUBTRACT, {line, column});
}

}     // namespace ThisFunc::AST
