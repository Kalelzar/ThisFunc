#ifndef AST_H
#define AST_H

#include <list>
#include <memory>
#include <string>

namespace ThisFunc {
namespace AST {

template <class A> using ASTPointer = std::shared_ptr<A>;

class Element {
public:
  virtual void print() = 0;
  virtual Element* printf(){
    print();
    return this;
  }
};
using ElementPtr = ASTPointer<Element>;

class Statement : public Element {
public:
  virtual void print() override = 0;
};

using StatementPtr = ASTPointer<Statement>;

class Expression : public Expression, public Statement {
public:
  virtual void print() override = 0;
  virtual Element* printf() override {
    print();
    return (Statement*) this;
  }
};
using ExpressionPtr = ASTPointer<Expression>;

class Number : public Expression {
public:
  Number(double number) : number(number) {}

  double number;
  void print() override;
};

using NumberPtr = ASTPointer<Number>;

class Identifier : public Element {
public:
  Identifier(std::string &) = delete;
  Identifier(std::string &&identifier) : identifier(identifier) {}

  void print() override;
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
};

using FuncallPtr = ASTPointer<Funcall>;

class Param : public Expression {
public:
  Param(std::string identifier) : identifier(identifier) {}

  void print() override;
  std::string identifier;
};

using ParamPtr = ASTPointer<Param>;

class Fundef : public Statement {
public:
  Fundef(IdentifierPtr name, ExpressionPtr body)
      : name(name), body(body) {}

  void print() override;
  IdentifierPtr name;
  ExpressionPtr body;
};

using FundefPtr = ASTPointer<Fundef>;

class Body : public Element {
public:
  void print() override;
  Body(std::list<StatementPtr> statements) : statements(statements) {}
  std::list<StatementPtr> statements;
};

using BodyPtr = ASTPointer<Body>;

} // namespace AST
} // namespace ThisFunc

#endif /* AST_H */
