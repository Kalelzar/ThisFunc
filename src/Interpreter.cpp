#include <ThisFunc/Interpreter.hpp>

namespace ThisFunc {

void Interpreter::precalculate ( ) {
  AST::BodyPtr newBody = ptr_cast<AST::Body> (body->optimal ( ));
  newBody->print ( );
  body = newBody;
}

void Interpreter::print ( ) { body->print ( ); }

}     // namespace ThisFunc
