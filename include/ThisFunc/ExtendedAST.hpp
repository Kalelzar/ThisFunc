#ifndef EXTENDEDAST_H
#define EXTENDEDAST_H

#include <ThisFunc/AST.hpp>

namespace ThisFunc::AST {

class SpecializedExpression : public Expression {

  public:
  SpecializedExpression (u32 line, u32 column) : Expression (line, column) { }
  using super = SpecializedExpression;
};

class Add : public SpecializedExpression {
  public:
  Add (ExpressionPtr lhs, ExpressionPtr rhs, u32 line, u32 column)
      : lhs (lhs)
      , rhs (rhs)
      , super (line, column) { }
  ExpressionPtr lhs, rhs;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

class Sub : public SpecializedExpression {
  public:
  Sub (ExpressionPtr lhs, ExpressionPtr rhs, u32 line, u32 column)
      : lhs (lhs)
      , rhs (rhs)
      , super (line, column) { }
  ExpressionPtr lhs, rhs;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

class Mul : public SpecializedExpression {
  public:
  Mul (ExpressionPtr lhs, ExpressionPtr rhs, u32 line, u32 column)
      : lhs (lhs)
      , rhs (rhs)
      , super (line, column) { }
  ExpressionPtr lhs, rhs;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

class Div : public SpecializedExpression {
  public:
  Div (ExpressionPtr lhs, ExpressionPtr rhs, u32 line, u32 column)
      : lhs (lhs)
      , rhs (rhs)
      , super ({rhs, lhs}, line, column) { }
  ExpressionPtr lhs, rhs;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

class Pow : public SpecializedExpression {
  public:
  Pow (ExpressionPtr lhs, ExpressionPtr rhs, u32 line, u32 column)
      : lhs (lhs)
      , rhs (rhs)
      , super (line, column) { }
  ExpressionPtr lhs, rhs;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

class Eq : public SpecializedExpression {
  public:
  Eq (ExpressionPtr lhs, ExpressionPtr rhs, u32 line, u32 column)
      : lhs (lhs)
      , rhs (rhs)
      , super (line, column) { }
  ExpressionPtr lhs, rhs;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

class Nand : public SpecializedExpression {
  public:
  Nand (ExpressionPtr lhs, ExpressionPtr rhs, u32 line, u32 column)
      : lhs (lhs)
      , rhs (rhs)
      , super (line, column) { }
  ExpressionPtr lhs, rhs;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

class Le : public SpecializedExpression {
  public:
  Le (ExpressionPtr lhs, ExpressionPtr rhs, u32 line, u32 column)
      : lhs (lhs)
      , rhs (rhs)
      , super (line, column) { }
  ExpressionPtr lhs, rhs;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

class If : public SpecializedExpression {
  public:
  If (ExpressionPtr cond,
      ExpressionPtr ifTrue,
      ExpressionPtr ifFalse,
      u32           line,
      u32           column)
      : cond (cond)
      , ifTrue (ifTrue)
      , ifFalse (ifFalse)
      , super (line, column) { }
  ExpressionPtr cond, ifTrue, ifFalse;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

class Sqrt : public SpecializedExpression {
  public:
  Sqrt (ExpressionPtr value, u32 line, u32 column)
      : value (value)
      , super (line, column){ };
  ExpressionPtr value;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

class Sin : public SpecializedExpression {
  public:
  Sin (ExpressionPtr value, u32 line, u32 column)
      : value (value)
      , super (line, column){ };
  ExpressionPtr value;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

class Cos : public SpecializedExpression {
  public:
  Cos (ExpressionPtr value, u32 line, u32 column)
      : value (value)
      , super (line, column){ };
  ExpressionPtr value;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

class List : public SpecializedExpression {
  public:
  List (std::list<ExpressionPtr>& values, u32 line, u32 column)
      : values (values)
      , super (line, column){ };
  List (std::list<ExpressionPtr>&& values, u32 line, u32 column)
      : values (values)
      , super (line, column){ };
  std::list<ExpressionPtr> values;
  void                     print (std::ostream*) override;
  void                     compile (VM::Chunk*) override;
  ElementPtr               optimal ( ) override;
};

using ListPtr = ASTPointer<List>;

class Head : public SpecializedExpression {
  public:
  Head (ListPtr value, u32 line, u32 column)
      : value (value)
      , super (line, column){ };
  ListPtr    value;
  void       print (std::ostream*) override;
  void       compile (VM::Chunk*) override;
  ElementPtr optimal ( ) override;
};

class Tail : public SpecializedExpression {
  public:
  Tail (ListPtr value, u32 line, u32 column)
      : value (value)
      , super (line, column){ };
  ListPtr    value;
  void       print (std::ostream*) override;
  void       compile (VM::Chunk*) override;
  ElementPtr optimal ( ) override;
};

class Map : public SpecializedExpression {
  public:
  Map (IdentifierPtr funname, ListPtr list, u32 line, u32 column)
      : funname (funname)
      , list (list)
      , super (line, column) { }
  IdentifierPtr funname;
  ListPtr       list;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

}     // namespace ThisFunc::AST

#endif /* EXTENDEDAST_H */
