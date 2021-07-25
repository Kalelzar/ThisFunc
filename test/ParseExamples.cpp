#include <ThisFunc/Parser.hpp>

#include <gtest/gtest.h>
#include <memory>
#include <rapidcheck/gtest.h>

#include <sstream>

using namespace ThisFunc;

TEST(ParseExample, CallAdd) {
  std::stringstream inout;
  inout << "add(3, 7)";
  Parser parser(&inout);
  AST::BodyPtr body = parser.parse();
  ASSERT_FALSE(parser.hadError);
  AST::FuncallPtr funcall =
    AST::ptr_cast<AST::Funcall>(body->statements.front());
  std::string funname = AST::ptr_cast<AST::Identifier>(funcall->name)->identifier;
  ASSERT_EQ(funname, "add");
  ASSERT_EQ(funcall->args.size(), 2);
  double lhs = AST::ptr_cast<AST::Number>(funcall->args.front())->number;
  ASSERT_DOUBLE_EQ(lhs, 3);
  double rhs = AST::ptr_cast<AST::Number>(funcall->args.back())->number;
  ASSERT_DOUBLE_EQ(rhs, 7);
}

TEST(ParseExample, CallAddInAdd) {
  std::stringstream inout;
  inout << "add(add(3, 5), add(10, 10))";
  Parser parser(&inout);
  AST::BodyPtr body = parser.parse();
  ASSERT_FALSE(parser.hadError);
  AST::FuncallPtr funcall =
      AST::ptr_cast<AST::Funcall>(body->statements.front());
  std::string funname = AST::ptr_cast<AST::Identifier>(funcall->name)->identifier;
  ASSERT_EQ(funname, "add");
  ASSERT_EQ(funcall->args.size(), 2);
  AST::FuncallPtr lhs = AST::ptr_cast<AST::Funcall>(funcall->args.front());
  ASSERT_EQ(AST::ptr_cast<AST::Identifier>(lhs->name)->identifier, "add");
  AST::FuncallPtr rhs = AST::ptr_cast<AST::Funcall>(funcall->args.back());
  ASSERT_EQ(AST::ptr_cast<AST::Identifier>(rhs->name)->identifier, "add");
}


TEST(ParseExample, DeclareConstant) {
  std::stringstream inout;
  inout << "myConst <- 7";
  Parser parser(&inout);
  AST::BodyPtr body = parser.parse();
  ASSERT_FALSE(parser.hadError);
  AST::FundefPtr fundef =
      AST::ptr_cast<AST::Fundef>(body->statements.front());
  std::string funname = AST::ptr_cast<AST::Identifier>(fundef->name)->identifier;
  ASSERT_EQ(funname, "myConst");
  double value = AST::ptr_cast<AST::Number>(fundef->body)->number;
  ASSERT_DOUBLE_EQ(value, 7);
}

TEST(ParseExample, CallConstant) {
  std::stringstream inout;
  inout << "myConst()";
  Parser parser(&inout);
  AST::BodyPtr body = parser.parse();
  ASSERT_FALSE(parser.hadError);
    AST::FuncallPtr funcall =
      AST::ptr_cast<AST::Funcall>(body->statements.front());
  std::string funname = AST::ptr_cast<AST::Identifier>(funcall->name)->identifier;
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
      AST::ptr_cast<AST::Fundef>(body->statements.front());
  std::string funname = AST::ptr_cast<AST::Identifier>(fundef->name)->identifier;
  ASSERT_EQ(funname, "doubleArg");
  AST::FuncallPtr funcall =
    AST::ptr_cast<AST::Funcall>(fundef->body);
  std::string funname2 = AST::ptr_cast<AST::Identifier>(funcall->name)->identifier;
  ASSERT_EQ(funname2, "add");
  ASSERT_EQ(funcall->args.size(), 2);
  auto& lhs = AST::ptr_cast<AST::Identifier>(funcall->args.front())->identifier;
  ASSERT_EQ(lhs, "#0");
  auto& rhs = AST::ptr_cast<AST::Identifier>(funcall->args.back())->identifier;
  ASSERT_EQ(rhs, "#0");
}
