#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <ThisFunc/AST.hpp>

namespace ThisFunc {
class Interpreter {
  public:
  Interpreter (AST::BodyPtr body) : body (body) { }

  //  void resolve();
  //  void specialize();

  //  void trueConstants();
  void precalculate ( );
  void print ( );

  private:
  AST::BodyPtr body;
};
}     // namespace ThisFunc

#endif /* INTERPRETER_H */
