#ifndef COMPILER_H
#define COMPILER_H

#include <ThisFunc/Chunk.hpp>
#include <ThisFunc/Parser.hpp>
#include <ThisFunc/Resolver.hpp>

namespace ThisFunc {

class Compiler {

  private:
  public:
  AST::Resolver compile (std::istream*, VM::Chunk*);
};

}     // namespace ThisFunc


#endif /* COMPILER_H */
