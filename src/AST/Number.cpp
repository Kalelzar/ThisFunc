#include "ThisFunc/Chunk.hpp"
#include <ThisFunc/AST.hpp>

#include <iostream>

namespace ThisFunc::AST {

  void Number::print() {
    std::cout<<number;
  }

  ElementPtr Number::optimal(){
    return std::make_shared<Number>(*this);
  }

  void Number::compile(VM::Chunk *chunk) {
    chunk->write(VM::OP_CONSTANT, {0, 0});
    chunk->write(chunk->addConstant(number), {0, 0});
  }

}
