#include <ThisFunc/Parser.hpp>

#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include <sstream>

using namespace ThisFunc;

RC_GTEST_PROP(Parser, aNumberIsANumber, (i32 a)) {
  std::stringstream inout;
  inout << a;
  Parser parser(&inout);
  AST::BodyPtr body = parser.parse();
  RC_ASSERT_FALSE(parser.hadError);
  RC_ASSERT(body->statements.size() == 1);
  // FIX: Implement lenses. It's a crime to leave it like that.
  RC_ASSERT(((AST::Number *)body->statements.front().get())->number == a);
}

RC_GTEST_PROP(Parser, aConstantCanHoldAValue, (i32 a)) {
  std::stringstream inout;
  inout << "const <- " << a;
  Parser parser(&inout);
  AST::BodyPtr body = parser.parse();
  RC_ASSERT_FALSE(parser.hadError);
  RC_ASSERT(body->statements.size() == 1);
  // FIX: Implement lenses. It's a crime to leave it like that.
  AST::Fundef *fundef = ((AST::Fundef *)body->statements.front().get());
  std::string name = fundef->name->identifier;
  RC_ASSERT(name == "const");
  i32 constant = ((AST::Number *)fundef->body.get())->number;
  RC_ASSERT(a == constant);
}

TEST(Parser, anIdentityExists) {
  std::stringstream inout;
  inout << "identity <- #0";
  Parser parser(&inout);
  AST::BodyPtr body = parser.parse();
  // FIX: Implement lenses. It's a crime to leave it like that.
  AST::Fundef *fundef = ((AST::Fundef *)body->statements.front().get());
  std::string name = fundef->name->identifier;
  ASSERT_FALSE(parser.hadError);
  ASSERT_EQ(name, "identity");
  std::string id = ((AST::Param *)fundef->body.get())->identifier;
  ASSERT_EQ(id, "#0");
}

RC_GTEST_PROP(Parser, parametersCanBeModified, (i32 a)) {
  std::stringstream inout;
  inout << "mod <- sqrt(" << a << ")";
  Parser parser(&inout);
  AST::BodyPtr body = parser.parse();
  RC_ASSERT_FALSE(parser.hadError);
  RC_ASSERT(body->statements.size() == 1);
  // FIX: Implement lenses. It's a crime to leave it like that.
  AST::Fundef *fundef = ((AST::Fundef *)body->statements.front().get());
  std::string name = fundef->name->identifier;
  RC_ASSERT(name == "mod");
  AST::Funcall *funcall = ((AST::Funcall *)fundef->body.get());
  std::string funname = funcall->name->identifier;
  RC_ASSERT(funname == "sqrt");
  auto args = funcall->args;
  RC_ASSERT(args.size() == 1);
  auto head = ((AST::Number *)args.front().get())->number;
  RC_ASSERT(head == a);
}

TEST(Parser, youCannotPassFunctionsAsArguments) {
  std::stringstream inout;
  inout << "lambda(epsilon)";
  Parser parser(&inout);
  AST::BodyPtr body = parser.parse();
  RC_ASSERT(parser.hadError);
}

TEST(Parser, youCannotUseParametersOutsideOfADefinition){
  std::stringstream inout;
  inout << "lambda(#0)";
  Parser parser(&inout);
  AST::BodyPtr body = parser.parse();
  RC_ASSERT(parser.hadError);
}

TEST(Parser, recursionIsPossible){
  std::stringstream inout;
  inout << "fact <- if(eq(#0, 0), 1, mul(#0, fact(sub(#0, 1))))";
  Parser parser(&inout);
  AST::BodyPtr body = parser.parse();
  RC_ASSERT(!parser.hadError);
}
