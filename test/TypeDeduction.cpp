#include <ThisFunc/Parser.hpp>
#include <ThisFunc/TypeDeduction.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <rapidcheck/Assertions.h>
#include <rapidcheck/gtest.h>

namespace ThisFunc::AST {

TEST (TypeDeduction, ANumberMeansNothingInDeduction) {
  Number     num (0, 0, 0);
  StackTrace st;
  Resolver   r;
  Function   f = deduce (std::make_shared<Number> (num), st, r);
  Function   o = { };
  ASSERT_TRUE (f == o);
}

TEST (TypeDeduction, AParameterAsIdentifierIsAmbiguous) {
  Resolver          r;
  std::stringstream inout;
  inout << "const <- #0";
  ThisFunc::Parser parser (&inout);
  BodyPtr          body = parser.parse ( );
  ASSERT_FALSE (parser.hadError);
  r.resolve (body);
  StackTrace st;
  Function   f = deduce (ptr_cast<Fundef> (body->statements.front ( )), st, r);
  ASSERT_TRUE (f.arguments[0]->isOfType (UnknownT));
}

TEST (TypeDeduction, AFundefHasAName) {
  Resolver          r;
  std::stringstream inout;
  inout << "const <- #0";
  ThisFunc::Parser parser (&inout);
  BodyPtr          body = parser.parse ( );
  ASSERT_FALSE (parser.hadError);
  r.resolve (body);
  StackTrace st;
  Function   f = deduce (ptr_cast<Fundef> (body->statements.front ( )), st, r);
  ASSERT_EQ (f.name, "const");
}

TEST (TypeDeduction, ANumericConstantReturnsANumber) {
  Resolver          r;
  std::stringstream inout;
  inout << "const <- 0";
  ThisFunc::Parser parser (&inout);
  BodyPtr          body = parser.parse ( );
  ASSERT_FALSE (parser.hadError);
  r.resolve (body);
  StackTrace st;
  Function   f = deduce (ptr_cast<Fundef> (body->statements.front ( )), st, r);
  ASSERT_EQ (f.returnType, NumberT);
}

TEST (TypeDeduction, AFunctionalConstantReturnsAFunction) {
  Resolver          r;
  std::stringstream inout;
  inout << "const <- function";
  ThisFunc::Parser parser (&inout);
  BodyPtr          body = parser.parse ( );
  ASSERT_FALSE (parser.hadError);
  r.resolve (body);
  StackTrace st;
  Function   f = deduce (ptr_cast<Fundef> (body->statements.front ( )), st, r);
  ASSERT_EQ (f.returnType, FunctionT);
}

TEST (TypeDeduction, AnIdentityReturnTypeisAmbiguous) {
  Resolver          r;
  std::stringstream inout;
  inout << "const <- #0";
  ThisFunc::Parser parser (&inout);
  BodyPtr          body = parser.parse ( );
  ASSERT_FALSE (parser.hadError);
  r.resolve (body);
  StackTrace st;
  Function   f = deduce (ptr_cast<Fundef> (body->statements.front ( )), st, r);
  ASSERT_EQ (f.returnType, UnknownT);
}
}     // namespace ThisFunc::AST
