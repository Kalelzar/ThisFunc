#include <ThisFunc/AST.hpp>
#include <ThisFunc/Chunk.hpp>
#include <ThisFunc/ExtendedAST.hpp>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace ThisFunc::AST {

void Div::print ( ) {
  std::cout << "(/ ";
  lhs->print ( );
  std::cout << " ";
  rhs->print ( );
  std::cout << ")";
}

void Div::compile (VM::Chunk* chunk) {
  lhs->compile (chunk);
  rhs->compile (chunk);
  chunk->write (VM::OP_DIVIDE, {line, column});
}

ElementPtr Div::optimal ( ) {
  ElementPtr nlhs = lhs->optimal ( );
  ElementPtr nrhs = rhs->optimal ( );

  if (nlhs->isNumber ( ) && nrhs->isNumber ( )) {
    double             lhsd = ptr_cast<Number> (nlhs)->number;
    double             rhsd = ptr_cast<Number> (nrhs)->number;
    std::ostringstream st;
    st << "Division by zero at " << line << ":" << column;
    if (std::fabs (rhsd) <= 1E-6) throw std::runtime_error (st.str ( ));
    return std::make_shared<Number> (lhsd / rhsd, line, column);
  }
  return std::make_shared<Div> (ptr_cast<Expression> (nlhs),
                                ptr_cast<Expression> (nrhs),
                                line,
                                column);
}

}     // namespace ThisFunc::AST
