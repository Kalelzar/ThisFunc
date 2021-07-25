#ifndef EXTENDEDAST_H
#define EXTENDEDAST_H

#include <ThisFunc/AST.hpp>

namespace ThisFunc::AST {

class SpecializedExpression : public Expression {};

class Add : public SpecializedExpression {
public:
  Add(ExpressionPtr lhs, ExpressionPtr rhs) : lhs(lhs), rhs(rhs) {}
  ExpressionPtr lhs, rhs;
  void print() override;
  ElementPtr optimal() override;
};

class Sub : public SpecializedExpression {
public:
  Sub(ExpressionPtr lhs, ExpressionPtr rhs) : lhs(lhs), rhs(rhs) {}
  ExpressionPtr lhs, rhs;
  void print() override;
  ElementPtr optimal() override;
};

class Mul : public SpecializedExpression {
public:
  Mul(ExpressionPtr lhs, ExpressionPtr rhs) : lhs(lhs), rhs(rhs) {}
  ExpressionPtr lhs, rhs;
  void print() override;
  ElementPtr optimal() override;
};

class Div : public SpecializedExpression {
public:
  Div(ExpressionPtr lhs, ExpressionPtr rhs) : lhs(lhs), rhs(rhs) {}
  ExpressionPtr lhs, rhs;
  void print() override;
  ElementPtr optimal() override;
};

class Pow : public SpecializedExpression {
public:
  Pow(ExpressionPtr lhs, ExpressionPtr rhs) : lhs(lhs), rhs(rhs) {}
  ExpressionPtr lhs, rhs;
  void print() override;
  ElementPtr optimal() override;
};

class Eq : public SpecializedExpression {
public:
  Eq(ExpressionPtr lhs, ExpressionPtr rhs) : lhs(lhs), rhs(rhs) {}
  ExpressionPtr lhs, rhs;
  void print() override;
  ElementPtr optimal() override;
};

class Nand : public SpecializedExpression {
public:
  Nand(ExpressionPtr lhs, ExpressionPtr rhs) : lhs(lhs), rhs(rhs) {}
  ExpressionPtr lhs, rhs;
  void print() override;
  ElementPtr optimal() override;
};

class Le : public SpecializedExpression {
public:
  Le(ExpressionPtr lhs, ExpressionPtr rhs) : lhs(lhs), rhs(rhs) {}
  ExpressionPtr lhs, rhs;
  void print() override;
  ElementPtr optimal() override;
};

class If : public SpecializedExpression {
public:
  If(ExpressionPtr cond, ExpressionPtr ifTrue, ExpressionPtr ifFalse)
      : cond(cond), ifTrue(ifTrue), ifFalse(ifFalse) {}
  ExpressionPtr cond, ifTrue, ifFalse;
  void print() override;
  ElementPtr optimal() override;
};

class Sqrt : public SpecializedExpression {
public:
  Sqrt(ExpressionPtr value) : value(value){};
  ExpressionPtr value;
  void print() override;
  ElementPtr optimal() override;
};

class Sin : public SpecializedExpression {
public:
  Sin(ExpressionPtr value) : value(value){};
  ExpressionPtr value;
  void print() override;
  ElementPtr optimal() override;
};

class Cos : public SpecializedExpression {
public:
  Cos(ExpressionPtr value) : value(value){};
  ExpressionPtr value;
  void print() override;
  ElementPtr optimal() override;
};

class List : public SpecializedExpression {
public:
  List(std::list<ExpressionPtr> &values) : values(values){};
  List(std::list<ExpressionPtr> &&values) : values(values){};
  std::list<ExpressionPtr> values;
  void print() override;
  ElementPtr optimal() override;
};

using ListPtr = ASTPointer<List>;

class Head : public SpecializedExpression {
public:
  Head(ListPtr value) : value(value){};
  ListPtr value;
  void print() override;
  ElementPtr optimal() override;
};

class Tail : public SpecializedExpression {
public:
  Tail(ListPtr value) : value(value){};
  ListPtr value;
  void print() override;
  ElementPtr optimal() override;
};

class Map : public SpecializedExpression {
public:
  Map(IdentifierPtr funname, ListPtr list) : funname(funname), list(list) {}
  IdentifierPtr funname;
  ListPtr list;
  void print() override;
  ElementPtr optimal() override;
};

} // namespace ThisFunc::AST

#endif /* EXTENDEDAST_H */
