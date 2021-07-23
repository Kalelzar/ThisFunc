#ifndef EXTENDEDAST_H
#define EXTENDEDAST_H

#include <ThisFunc/AST.hpp>

namespace ThisFunc::AST {

class Add : public Expression {
public:
  Add(ExpressionPtr lhs, ExpressionPtr rhs) : lhs(lhs), rhs(rhs) {}
  ExpressionPtr lhs, rhs;
  void print() override;
  ElementPtr optimal() override;
};

class Sub : public Expression {
public:
  Sub(ExpressionPtr lhs, ExpressionPtr rhs) : lhs(lhs), rhs(rhs) {}
  ExpressionPtr lhs, rhs;
  void print() override;
  ElementPtr optimal() override;
};

class Mul : public Expression {
public:
  Mul(ExpressionPtr lhs, ExpressionPtr rhs) : lhs(lhs), rhs(rhs) {}
  ExpressionPtr lhs, rhs;
  void print() override;
  ElementPtr optimal() override;
};

class Div : public Expression {
public:
  Div(ExpressionPtr lhs, ExpressionPtr rhs) : lhs(lhs), rhs(rhs) {}
  ExpressionPtr lhs, rhs;
  void print() override;
  ElementPtr optimal() override;
};

class Pow : public Expression {
public:
  Pow(ExpressionPtr lhs, ExpressionPtr rhs) : lhs(lhs), rhs(rhs) {}
  ExpressionPtr lhs, rhs;
  void print() override;
  ElementPtr optimal() override;
};

class Eq : public Expression {
public:
  Eq(ExpressionPtr lhs, ExpressionPtr rhs) : lhs(lhs), rhs(rhs) {}
  ExpressionPtr lhs, rhs;
  void print() override;
  ElementPtr optimal() override;
};

class Nand : public Expression {
public:
  Nand(ExpressionPtr lhs, ExpressionPtr rhs) : lhs(lhs), rhs(rhs) {}
  ExpressionPtr lhs, rhs;
  void print() override;
  ElementPtr optimal() override;
};

class Le : public Expression {
public:
  Le(ExpressionPtr lhs, ExpressionPtr rhs) : lhs(lhs), rhs(rhs) {}
  ExpressionPtr lhs, rhs;
  void print() override;
  ElementPtr optimal() override;
};

class If : public Expression {
public:
  If(ExpressionPtr cond, ExpressionPtr ifTrue, ExpressionPtr ifFalse)
      : cond(cond), ifTrue(ifTrue), ifFalse(ifFalse) {}
  ExpressionPtr cond, ifTrue, ifFalse;
  void print() override;
  ElementPtr optimal() override;
};

} // namespace ThisFunc::AST

#endif /* EXTENDEDAST_H */
