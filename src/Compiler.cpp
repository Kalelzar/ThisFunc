#include "ThisFunc/AST.hpp"
#include <ThisFunc/Compiler.hpp>

namespace ThisFunc {
  bool Compiler::compile(std::istream * in, VM::Chunk* bytecode){
    Parser parser(in);

    AST::BodyPtr result = parser.parse();
    if(parser.hadError){
      std::cerr<<"Compilation unsuccessful."<<std::endl;
      return false;
    }

    result->optimal()->compile(bytecode);

    return true;
  }
}
