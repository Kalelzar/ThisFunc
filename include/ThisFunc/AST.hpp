#ifndef AST_H
#define AST_H

#include <list>
#include <memory>
#include <string>
#include <type_traits>

namespace ThisFunc {
namespace AST {



template <class A> using ASTPointer = std::shared_ptr<A>;



class Element {
public:
  virtual void print() = 0;

  virtual ASTPointer<Element> optimal() = 0;
  virtual bool isNumber() { return false; }
  virtual bool isParameter() { return false; }
  virtual Element *printf() {
    print();
    return this;
  }
};

template <typename A, typename B>
AST::ASTPointer<A> ptr_cast(AST::ASTPointer<B> b){
  return std::static_pointer_cast<A>(b);
}

using ElementPtr = ASTPointer<Element>;

class Statement : public Element {
public:
  virtual void print() override = 0;
};

using StatementPtr = ASTPointer<Statement>;

class Expression : public Statement {
public:
  virtual void print() override = 0;
};
using ExpressionPtr = ASTPointer<Expression>;

class Number : public Expression {
public:
  Number(double number) : number(number) {}

  double number;
  void print() override;
  ASTPointer<Element> optimal() override;
  bool isNumber() override { return true; }
};

using NumberPtr = ASTPointer<Number>;

class Identifier : public Element {
public:
  Identifier(std::string &) = delete;
  Identifier(std::string &&identifier) : identifier(identifier) {}

  void print() override;
  ASTPointer<Element> optimal() override;
  std::string identifier;
};

using IdentifierPtr = ASTPointer<Identifier>;

class Funcall : public Expression {
public:
  Funcall(IdentifierPtr name, std::list<ExpressionPtr> &&args)
      : name(name), args(args) {}

  IdentifierPtr name;
  std::list<ExpressionPtr> args;
  void print() override;
  ASTPointer<Element> optimal() override;
};

using FuncallPtr = ASTPointer<Funcall>;

class Param : public Expression {
public:
  Param(std::string identifier) : identifier(identifier) {}

  void print() override;
  ASTPointer<Element> optimal() override;
  bool isParameter() override { return true; }

  std::string identifier;
};

using ParamPtr = ASTPointer<Param>;

class Fundef : public Statement {
public:
  Fundef(IdentifierPtr name, ExpressionPtr body) : name(name), body(body) {}

  void print() override;
  ASTPointer<Element> optimal() override;

  IdentifierPtr name;
  ExpressionPtr body;
};

using FundefPtr = ASTPointer<Fundef>;

class Body : public Element {
public:
  void print() override;
  ElementPtr optimal() override;
  Body(std::list<StatementPtr> statements) : statements(statements) {}
  std::list<StatementPtr> statements;
};

using BodyPtr = ASTPointer<Body>;

} // namespace AST
} // namespace ThisFunc

#endif /* AST_H */
