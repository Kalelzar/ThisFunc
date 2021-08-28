#include <ThisFunc/AST.hpp>
#include <ThisFunc/Chunk.hpp>
#include <ThisFunc/ExtendedAST.hpp>
#include <cmath>
#include <iostream>
#include <memory>

namespace ThisFunc::AST {

void Filter::print (std::ostream* out) {
  *out << "(filter #'";
  funname->print (out);
  *out << " ";
  list->print (out);
  *out << ")";
}

ElementPtr Filter::optimal ( ) {
  return std::make_shared<Filter> (funname,
                                   ptr_cast<List> (list->optimal ( )),
                                   line,
                                   column);     // FIX: Placeholderx
}

void Filter::compile (VM::Chunk* chunk, Resolver& resolver) {
  list->unfurl (chunk, resolver, funname, VM::OP_FILTER);
}

}     // namespace ThisFunc::AST
