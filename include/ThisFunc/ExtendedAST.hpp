#ifndef EXTENDEDAST_H
#define EXTENDEDAST_H

#include <ThisFunc/AST.hpp>

namespace ThisFunc::AST {


class SpecializedExpression : public Funcall {

  private:
  virtual IdentifierPtr spec ( ) {
    return std::make_shared<Identifier> ("spec", 0, 0);
  }

  public:
  SpecializedExpression (std::list<ExpressionPtr> args, u32 line, u32 column)
      : Funcall (spec ( ), std::move (args), line, column) { }
  using super = SpecializedExpression;
};

class Add : public SpecializedExpression {
  private:
  virtual IdentifierPtr spec ( ) override {
    return std::make_shared<Identifier> ("add", 0, 0);
  }
  public:
  Add (ExpressionPtr lhs, ExpressionPtr rhs, u32 line, u32 column)
      : lhs (lhs)
      , rhs (rhs)
      , super ({rhs, lhs}, line, column) { }
  ExpressionPtr lhs, rhs;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

class Sub : public SpecializedExpression {
  private:
  virtual IdentifierPtr spec ( ) override {
    return std::make_shared<Identifier> ("sub", 0, 0);
  }
  public:
  Sub (ExpressionPtr lhs, ExpressionPtr rhs, u32 line, u32 column)
      : lhs (lhs)
      , rhs (rhs)
      , super ({rhs, lhs}, line, column) { }
  ExpressionPtr lhs, rhs;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

class Mul : public SpecializedExpression {
  private:
  virtual IdentifierPtr spec ( ) override {
    return std::make_shared<Identifier> ("mul", 0, 0);
  }
  public:
  Mul (ExpressionPtr lhs, ExpressionPtr rhs, u32 line, u32 column)
      : lhs (lhs)
      , rhs (rhs)
      , super ({rhs, lhs}, line, column) { }
  ExpressionPtr lhs, rhs;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

class Div : public SpecializedExpression {
  private:
  virtual IdentifierPtr spec ( ) override {
    return std::make_shared<Identifier> ("div", 0, 0);
  }
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
  private:
  virtual IdentifierPtr spec ( ) override {
    return std::make_shared<Identifier> ("pow", 0, 0);
  }
  public:
  Pow (ExpressionPtr lhs, ExpressionPtr rhs, u32 line, u32 column)
      : lhs (lhs)
      , rhs (rhs)
      , super ({rhs, lhs}, line, column) { }
  ExpressionPtr lhs, rhs;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

class Eq : public SpecializedExpression {
  private:
  virtual IdentifierPtr spec ( ) override {
    return std::make_shared<Identifier> ("eq", 0, 0);
  }
  public:
  Eq (ExpressionPtr lhs, ExpressionPtr rhs, u32 line, u32 column)
      : lhs (lhs)
      , rhs (rhs)
      , super ({rhs, lhs}, line, column) { }
  ExpressionPtr lhs, rhs;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

class Nand : public SpecializedExpression {
  private:
  virtual IdentifierPtr spec ( ) override {
    return std::make_shared<Identifier> ("nand", 0, 0);
  }
  public:
  Nand (ExpressionPtr lhs, ExpressionPtr rhs, u32 line, u32 column)
      : lhs (lhs)
      , rhs (rhs)
      , super ({rhs, lhs}, line, column) { }
  ExpressionPtr lhs, rhs;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

class Le : public SpecializedExpression {
  private:
  virtual IdentifierPtr spec ( ) override {
    return std::make_shared<Identifier> ("le", 0, 0);
  }
  public:
  Le (ExpressionPtr lhs, ExpressionPtr rhs, u32 line, u32 column)
      : lhs (lhs)
      , rhs (rhs)
      , super ({rhs, lhs}, line, column) { }
  ExpressionPtr lhs, rhs;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

class If : public SpecializedExpression {
  private:
  virtual IdentifierPtr spec ( ) override {
    return std::make_shared<Identifier> ("if", 0, 0);
  }
  public:
  If (ExpressionPtr cond,
      ExpressionPtr ifTrue,
      ExpressionPtr ifFalse,
      u32           line,
      u32           column)
      : cond (cond)
      , ifTrue (ifTrue)
      , ifFalse (ifFalse)
      , super ({cond, ifTrue, ifFalse}, line, column) { }
  ExpressionPtr cond, ifTrue, ifFalse;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

class Sqrt : public SpecializedExpression {
  private:
  virtual IdentifierPtr spec ( ) override {
    return std::make_shared<Identifier> ("sqrt", 0, 0);
  }
  public:
  Sqrt (ExpressionPtr value, u32 line, u32 column)
      : value (value)
      , super ({value}, line, column){ };
  ExpressionPtr value;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

class Sin : public SpecializedExpression {
  private:
  virtual IdentifierPtr spec ( ) override {
    return std::make_shared<Identifier> ("sin", 0, 0);
  }
  public:
  Sin (ExpressionPtr value, u32 line, u32 column)
      : value (value)
      , super ({value}, line, column){ };
  ExpressionPtr value;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

class Cos : public SpecializedExpression {
  private:
  virtual IdentifierPtr spec ( ) override {
    return std::make_shared<Identifier> ("cos", 0, 0);
  }
  public:
  Cos (ExpressionPtr value, u32 line, u32 column)
      : value (value)
      , super ({value}, line, column){ };
  ExpressionPtr value;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

class List : public SpecializedExpression {
  private:
  virtual IdentifierPtr spec ( ) override {
    return std::make_shared<Identifier> ("list", 0, 0);
  }
  public:
  List (std::list<ExpressionPtr>& values, u32 line, u32 column)
      : values (values)
      , super (values, line, column){ };
  List (std::list<ExpressionPtr>&& values, u32 line, u32 column)
      : values (values)
      , super (values, line, column){ };
  std::list<ExpressionPtr> values;
  void                     print (std::ostream*) override;
  void                     compile (VM::Chunk*) override;
  ElementPtr               optimal ( ) override;
};

using ListPtr = ASTPointer<List>;

class Head : public SpecializedExpression {
  private:
  virtual IdentifierPtr spec ( ) override {
    return std::make_shared<Identifier> ("head", 0, 0);
  }
  public:
  Head (ListPtr value, u32 line, u32 column)
      : value (value)
      , super ({value}, line, column){ };
  ListPtr    value;
  void       print (std::ostream*) override;
  void       compile (VM::Chunk*) override;
  ElementPtr optimal ( ) override;
};

class Tail : public SpecializedExpression {
  private:
  virtual IdentifierPtr spec ( ) override {
    return std::make_shared<Identifier> ("tail", 0, 0);
  }
  public:
  Tail (ListPtr value, u32 line, u32 column)
      : value (value)
      , super ({value}, line, column){ };
  ListPtr    value;
  void       print (std::ostream*) override;
  void       compile (VM::Chunk*) override;
  ElementPtr optimal ( ) override;
};

class Map : public SpecializedExpression {
  private:
  virtual IdentifierPtr spec ( ) override {
    return std::make_shared<Identifier> ("map", 0, 0);
  }
  public:
  Map (IdentifierPtr funname, ListPtr list, u32 line, u32 column)
      : funname (funname)
      , list (list)
      , super ({funname, list}, line, column) { }
  IdentifierPtr funname;
  ListPtr       list;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*) override;
  ElementPtr    optimal ( ) override;
};

}     // namespace ThisFunc::AST

#endif /* EXTENDEDAST_H */
