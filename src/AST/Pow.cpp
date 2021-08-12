#include <ThisFunc/AST.hpp>
#include <ThisFunc/ExtendedAST.hpp>
#include <cmath>
#include <iostream>

namespace ThisFunc::AST {

void Pow::print (std::ostream* out) {
  *out << "(pow ";
  lhs->print (out);
  *out << " ";
  rhs->print (out);
  *out << ")";
}

ElementPtr Pow::optimal ( ) {
  ElementPtr nlhs = lhs->optimal ( );
  ElementPtr nrhs = rhs->optimal ( );

  if (nlhs->isNumber ( ) && nrhs->isNumber ( )) {
    double lhsd = ptr_cast<Number> (nlhs)->number;
    double rhsd = ptr_cast<Number> (nrhs)->number;
    return std::make_shared<Number> (std::pow (lhsd, rhsd), line, column);
  }
  return std::make_shared<Pow> (ptr_cast<Expression> (nlhs),
                                ptr_cast<Expression> (nrhs),
                                line,
                                column);
}

void Pow::compile (VM::Chunk* chunk, Resolver& resolver) {
  chunk->write (VM::OP_POW, {line, column});
}

}     // namespace ThisFunc::AST
