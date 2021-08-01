#include <ThisFunc/AST.hpp>
#include <ThisFunc/ExtendedAST.hpp>
#include <cmath>
#include <iostream>

namespace ThisFunc::AST {

void Cos::print (std::ostream* out) {
  *out << "(cos ";
  value->print (out);
  *out << ")";
}

void Cos::compile (VM::Chunk* chunk) {
  chunk->write (VM::NOOP, {line, column});
}

/**
 * @copydoc Element::optimal
 * @details An optimal Cos is one which:
              <br>1) if it's argument optimizes to a Number: A Number
containing the cosine of the argument
              <br>2) otherwise: a Cos with an optimal argument
 */
ElementPtr Cos::optimal ( ) {
  ElementPtr val = value->optimal ( );

  if (value->isNumber ( )) {
    double num = ptr_cast<Number> (val)->number;
    return std::make_shared<Number> (std::cos (num), line, column);
  }
  return std::make_shared<Cos> (ptr_cast<Expression> (val), line, column);
}

}     // namespace ThisFunc::AST
