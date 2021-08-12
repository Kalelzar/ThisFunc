#include <ThisFunc/AST.hpp>
#include <ThisFunc/Chunk.hpp>
#include <ThisFunc/ExtendedAST.hpp>
#include <ThisFunc/Resolver.hpp>
#include <cmath>
#include <iostream>

namespace ThisFunc::AST {

void Add::print (std::ostream* out) {
  *out << "(+ ";
  lhs->print (out);
  *out << " ";
  rhs->print (out);
  *out << ")";
}

void Add::compile (VM::Chunk* chunk, Resolver& resolver) {
  lhs->compile (chunk, resolver);
  rhs->compile (chunk, resolver);
  chunk->write (VM::OP_ADD, {line, column});
}

/**
 * @copydoc Element::optimal
 * @details An optimal Add is one which:
              <br>1) if both of it's arguments optimize to a Number: A Number
containing their sum
              <br>2) otherwise: an Add with optimal arguments
 */
ElementPtr Add::optimal ( ) {
  ElementPtr nlhs = lhs->optimal ( );
  ElementPtr nrhs = rhs->optimal ( );

  if (nlhs->isNumber ( ) && nrhs->isNumber ( )) {
    double lhsd = ptr_cast<Number> (nlhs)->number;
    double rhsd = ptr_cast<Number> (nrhs)->number;
    return std::make_shared<Number> (lhsd + rhsd, line, column);
  }
  return std::make_shared<Add> (ptr_cast<Expression> (nlhs),
                                ptr_cast<Expression> (nrhs),
                                line,
                                column);
}

}     // namespace ThisFunc::AST
