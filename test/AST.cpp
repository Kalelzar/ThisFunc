#include <ThisFunc/Parser.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <rapidcheck/gtest.h>
#include <sstream>


namespace ThisFunc {

TEST (AST, FundefArityOfZero) {
  std::stringstream inout;
  inout << "const <- 5";
  Parser       parser (&inout);
  AST::BodyPtr body = parser.parse ( );
  ASSERT_FALSE (parser.hadError);
  AST::FundefPtr fundef
    = AST::ptr_cast<AST::Fundef> (body->statements.front ( ));
  ASSERT_EQ (fundef->arity ( ), 0);
}


TEST (AST, FundefArityOfOne) {
  std::stringstream inout;
  inout << "id <- #0";
  Parser       parser (&inout);
  AST::BodyPtr body = parser.parse ( );
  ASSERT_FALSE (parser.hadError);
  AST::FundefPtr fundef
    = AST::ptr_cast<AST::Fundef> (body->statements.front ( ));
  ASSERT_EQ (fundef->arity ( ), 1);
}

TEST (AST, FundefArityOf1WithRepeats) {
  std::stringstream inout;
  inout << "double <- add(#0, #0)";
  Parser       parser (&inout);
  AST::BodyPtr body = parser.parse ( );
  ASSERT_FALSE (parser.hadError);
  AST::FundefPtr fundef
    = AST::ptr_cast<AST::Fundef> (body->statements.front ( ));
  ASSERT_EQ (fundef->arity ( ), 1);
}

RC_GTEST_PROP (AST, FundefArityOfN, ( )) {
  u32               arity = *rc::gen::inRange (0, 16);
  std::stringstream inout;
  inout << "double <- list(";
  for (int i = 0; i < arity; i++) {
    inout << "#" << i;
    if (i != arity - 1) { inout << ","; }
  }
  inout << ")";
  Parser       parser (&inout);
  AST::BodyPtr body = parser.parse ( );
  RC_ASSERT_FALSE (parser.hadError);
  AST::FundefPtr fundef
    = AST::ptr_cast<AST::Fundef> (body->statements.front ( ));
  RC_ASSERT (fundef->arity ( ) == arity);
}

RC_GTEST_PROP (AST, FundefArityOfNSingleArgument, ( )) {
  u32               arity = *rc::gen::inRange (1, 16);
  std::stringstream inout;
  inout << "double <- sqrt(";
  inout << "#" << (arity - 1);
  inout << ")";
  Parser       parser (&inout);
  AST::BodyPtr body = parser.parse ( );
  RC_ASSERT_FALSE (parser.hadError);
  AST::FundefPtr fundef
    = AST::ptr_cast<AST::Fundef> (body->statements.front ( ));
  RC_ASSERT (fundef->arity ( ) == arity);
}

}     // namespace ThisFunc
