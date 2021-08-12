#include <ThisFunc/AST.hpp>
#include <ThisFunc/ExtendedAST.hpp>
#include <cmath>
#include <iostream>
#include <memory>

namespace ThisFunc::AST {

void Head::print (std::ostream* out) {
  *out << "(car ";
  value->print (out);
  *out << ")";
}

ElementPtr Head::optimal ( ) {
  if (value->values.size ( ) >= 1)
    return value->values.front ( )->optimal ( );
  else
    return std::make_shared<List> (std::list<ExpressionPtr> ( ), line, column);
}

void Head::compile (VM::Chunk* chunk, Resolver& resolver) {
  chunk->write (VM::OP_HEAD, {line, column});
}

}     // namespace ThisFunc::AST
