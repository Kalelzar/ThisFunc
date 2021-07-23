#include <ThisFunc/Parser.hpp>

#include <gtest/gtest.h>
#include <memory>
#include <rapidcheck/gtest.h>

#include <sstream>

using namespace ThisFunc;

template <typename A, typename B>
AST::ASTPointer<A> ptr_cast(AST::ASTPointer<B> b){
  return std::static_pointer_cast<A>(b);
}

TEST(ParseExample, CallAdd) {
  std::stringstream inout;
  inout << "add(3, 7)";
  Parser parser(&inout);
  AST::BodyPtr body = parser.parse();
  ASSERT_FALSE(parser.hadError);
  AST::FuncallPtr funcall =
      ptr_cast<AST::Funcall>(body->statements.front());
  std::string funname = ptr_cast<AST::Identifier>(funcall->name)->identifier;
  ASSERT_EQ(funname, "add");
  ASSERT_EQ(funcall->args.size(), 2);
  double lhs = ptr_cast<AST::Number>(funcall->args.front())->number;
  ASSERT_DOUBLE_EQ(lhs, 3);
  double rhs = ptr_cast<AST::Number>(funcall->args.back())->number;
  ASSERT_DOUBLE_EQ(rhs, 7);
}

TEST(ParseExample, CallAddInAdd) {
  std::stringstream inout;
  inout << "add(add(3, 5), add(10, 10))";
  Parser parser(&inout);
  AST::BodyPtr body = parser.parse();
  ASSERT_FALSE(parser.hadError);
  AST::FuncallPtr funcall =
      ptr_cast<AST::Funcall>(body->statements.front());
  std::string funname = ptr_cast<AST::Identifier>(funcall->name)->identifier;
  ASSERT_EQ(funname, "add");
  ASSERT_EQ(funcall->args.size(), 2);
  AST::FuncallPtr lhs = ptr_cast<AST::Funcall>(funcall->args.front());
  ASSERT_EQ(ptr_cast<AST::Identifier>(lhs->name)->identifier, "add");
  AST::FuncallPtr rhs = ptr_cast<AST::Funcall>(funcall->args.back());
  ASSERT_EQ(ptr_cast<AST::Identifier>(rhs->name)->identifier, "add");
}


TEST(ParseExample, DeclareConstant) {
  std::stringstream inout;
  inout << "myConst <- 7";
  Parser parser(&inout);
  AST::BodyPtr body = parser.parse();
  ASSERT_FALSE(parser.hadError);
  AST::FundefPtr fundef =
      ptr_cast<AST::Fundef>(body->statements.front());
  std::string funname = ptr_cast<AST::Identifier>(fundef->name)->identifier;
  ASSERT_EQ(funname, "myConst");
  double value = ptr_cast<AST::Number>(fundef->body)->number;
  ASSERT_DOUBLE_EQ(value, 7);
}

TEST(ParseExample, CallConstant) {
  std::stringstream inout;
  inout << "myConst()";
  Parser parser(&inout);
  AST::BodyPtr body = parser.parse();
  ASSERT_FALSE(parser.hadError);
    AST::FuncallPtr funcall =
      ptr_cast<AST::Funcall>(body->statements.front());
  std::string funname = ptr_cast<AST::Identifier>(funcall->name)->identifier;
  ASSERT_EQ(funname, "myConst");
  ASSERT_EQ(funcall->args.size(), 0);
}

TEST(ParseExample, DeclareSimpleFunction) {
  std::stringstream inout;
  inout << "doubleArg <- add(#0, #0)";
  Parser parser(&inout);
  AST::BodyPtr body = parser.parse();
  ASSERT_FALSE(parser.hadError);
  AST::FundefPtr fundef =
      ptr_cast<AST::Fundef>(body->statements.front());
  std::string funname = ptr_cast<AST::Identifier>(fundef->name)->identifier;
  ASSERT_EQ(funname, "doubleArg");
  AST::FuncallPtr funcall =
    ptr_cast<AST::Funcall>(fundef->body);
  std::string funname2 = ptr_cast<AST::Identifier>(funcall->name)->identifier;
  ASSERT_EQ(funname2, "add");
  ASSERT_EQ(funcall->args.size(), 2);
  auto& lhs = ptr_cast<AST::Param>(funcall->args.front())->identifier;
  ASSERT_EQ(lhs, "#0");
  auto& rhs = ptr_cast<AST::Param>(funcall->args.back())->identifier;
  ASSERT_EQ(rhs, "#0");
}
