#include <ThisFunc/AST.hpp>
#include <ThisFunc/ExtendedAST.hpp>
#include <cmath>
#include <iostream>
#include <string>

namespace ThisFunc::AST {

void Nand::print (std::ostream* out) {
  *out << "(not (and";
  lhs->print (out);
  *out << " ";
  rhs->print (out);
  *out << "))";
}

ElementPtr Nand::optimal ( ) {
  ElementPtr nlhs = lhs->optimal ( );
  ElementPtr nrhs = rhs->optimal ( );

  if (nlhs->isNumber ( ) && nrhs->isNumber ( )) {
    double lhsd = ptr_cast<Number> (nlhs)->number;
    double rhsd = ptr_cast<Number> (nrhs)->number;
    return std::make_shared<Number> (
      std::fabs (lhsd) >= 1E-6 || std::fabs (lhsd) >= 1E-6 ? 1 : 0,
      line,
      column);
  }
  return std::make_shared<Nand> (ptr_cast<Expression> (nlhs),
                                 ptr_cast<Expression> (nrhs),
                                 line,
                                 column);
}

void Nand::compile (VM::Chunk* chunk) {
  chunk->write (VM::NOOP, {line, column});
}

}     // namespace ThisFunc::AST
