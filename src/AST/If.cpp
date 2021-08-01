#include <ThisFunc/AST.hpp>
#include <ThisFunc/ExtendedAST.hpp>
#include <cmath>
#include <iostream>

namespace ThisFunc::AST {

void If::print (std::ostream* out) {
  *out << "(if ";
  cond->print (out);
  *out << " ";
  ifTrue->print (out);
  *out << " ";
  ifFalse->print (out);
  *out << ")";
}

ElementPtr If::optimal ( ) {
  ElementPtr newCond = cond->optimal ( );

  if (cond->isNumber ( )) {
    double eval = ptr_cast<Number> (cond)->number;
    if (std::fabs (eval) <= 1E-6) {
      return ifFalse->optimal ( );
    } else {
      return ifTrue->optimal ( );
    }
  }

  return std::make_shared<If> (ptr_cast<Expression> (newCond),
                               ptr_cast<Expression> (ifTrue->optimal ( )),
                               ptr_cast<Expression> (ifFalse->optimal ( )),
                               line,
                               column);
}

void If::compile (VM::Chunk* chunk) { chunk->write (VM::NOOP, {line, column}); }

}     // namespace ThisFunc::AST
