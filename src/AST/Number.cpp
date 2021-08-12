#include <ThisFunc/AST.hpp>
#include <ThisFunc/Chunk.hpp>
#include <iostream>

namespace ThisFunc::AST {

void       Number::print (std::ostream* out) { *out << number; }

ElementPtr Number::optimal ( ) { return std::make_shared<Number> (*this); }

void       Number::compile (VM::Chunk* chunk, Resolver& resolver) {
  chunk->write (VM::OP_CONSTANT, {line, column});
  chunk->write (chunk->addConstant (number), {line, column});
}

}     // namespace ThisFunc::AST
