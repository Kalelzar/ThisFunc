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
  /**
   * @brief      Print the AST node to stdout
   *
   * @details    Uses a Lisp-like syntax.
   */
  virtual void print() = 0;

  /**
   * @brief      Return an optimal version of the AST node
   */
  virtual ASTPointer<Element> optimal() = 0;
  /// @brief Returns true if the instance is and instance of Number and false
  /// otherwise
  virtual bool isNumber() { return false; }
  /// @brief Returns true if the instance is and instance of Identifier and
  /// false otherwise
  virtual bool isIdentifier() { return false; }
};

/**
 * @brief      Casts an ASTPointer<B> into ASTPointer<A>
 *
 * @details    A wrapper around std::static_pointer_cast that ensures the
 *             arguments are ASTPointer for better static type-checking
 *
 *
 * @param      b the old pointer
 * @type_param A the type of the new pointer
 * @type_param B the type of the old pointer
 * @return     the new pointer
 */
template <typename A, typename B>
AST::ASTPointer<A> ptr_cast(AST::ASTPointer<B> b) {
  return std::static_pointer_cast<A>(b);
}

using ElementPtr = ASTPointer<Element>;

class Statement : public Element {};

using StatementPtr = ASTPointer<Statement>;

class Expression : public Statement {};
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

class Identifier : public Expression {
public:
  Identifier(std::string &) = delete;
  Identifier(std::string &&identifier) : identifier(identifier) {}

  void print() override;
  ASTPointer<Element> optimal() override;
  std::string identifier;
  bool isIdentifier() override { return true; }
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
  Body(std::list<StatementPtr> &statements) : statements(statements) {}
  Body(std::list<StatementPtr> &&statements) : statements(statements) {}
  std::list<StatementPtr> statements;
};

using BodyPtr = ASTPointer<Body>;

} // namespace AST
} // namespace ThisFunc

#endif /* AST_H */
