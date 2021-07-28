#include <ThisFunc/AST.hpp>
#include <ThisFunc/ExtendedAST.hpp>
#include <cmath>
#include <iostream>

namespace ThisFunc::AST {

void Le::print ( ) {
  std::cout << "(<= ";
  lhs->print ( );
  std::cout << " ";
  rhs->print ( );
  std::cout << ")";
}

ElementPtr Le::optimal ( ) {
  ElementPtr nlhs = lhs->optimal ( );
  ElementPtr nrhs = rhs->optimal ( );

  if (nlhs->isNumber ( ) && nrhs->isNumber ( )) {
    double lhsd = ptr_cast<Number> (nlhs)->number;
    double rhsd = ptr_cast<Number> (nrhs)->number;
    return std::make_shared<Number> (lhsd <= rhsd ? 1 : 0, line, column);
  }
  return std::make_shared<Le> (ptr_cast<Expression> (nlhs),
                               ptr_cast<Expression> (nrhs),
                               line,
                               column);
}

void Le::compile (VM::Chunk* chunk) { chunk->write (VM::NOOP, {line, column}); }

}     // namespace ThisFunc::AST
