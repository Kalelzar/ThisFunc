#ifndef EXTENDEDAST_H
#define EXTENDEDAST_H

#include <ThisFunc/AST.hpp>
#include <memory>

namespace ThisFunc::AST {


class SpecializedExpression : public Funcall {

  public:
  SpecializedExpression (std::string&&            name,
                         std::list<ExpressionPtr> args,
                         u32                      line,
                         u32                      column)
      : Funcall (std::make_shared<Identifier> (std::move (name), 0, 0),
                 std::move (args),
                 line,
                 column) { }
  using super = SpecializedExpression;
};

class Add : public SpecializedExpression {
  public:
  Add (ExpressionPtr lhs, ExpressionPtr rhs, u32 line, u32 column)
      : lhs (lhs)
      , rhs (rhs)
      , super ("add", {rhs, lhs}, line, column) { }
  ExpressionPtr lhs, rhs;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*, Resolver&) override;
  ElementPtr    optimal ( ) override;
};

class Sub : public SpecializedExpression {
  public:
  Sub (ExpressionPtr lhs, ExpressionPtr rhs, u32 line, u32 column)
      : lhs (lhs)
      , rhs (rhs)
      , super ("sub", {rhs, lhs}, line, column) { }
  ExpressionPtr lhs, rhs;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*, Resolver&) override;
  ElementPtr    optimal ( ) override;
};

class Mul : public SpecializedExpression {
  public:
  Mul (ExpressionPtr lhs, ExpressionPtr rhs, u32 line, u32 column)
      : lhs (lhs)
      , rhs (rhs)
      , super ("mul", {rhs, lhs}, line, column) { }
  ExpressionPtr lhs, rhs;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*, Resolver&) override;
  ElementPtr    optimal ( ) override;
};

class Div : public SpecializedExpression {
  public:
  Div (ExpressionPtr lhs, ExpressionPtr rhs, u32 line, u32 column)
      : lhs (lhs)
      , rhs (rhs)
      , super ("div", {rhs, lhs}, line, column) { }
  ExpressionPtr lhs, rhs;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*, Resolver&) override;
  ElementPtr    optimal ( ) override;
};

class Pow : public SpecializedExpression {
  public:
  Pow (ExpressionPtr lhs, ExpressionPtr rhs, u32 line, u32 column)
      : lhs (lhs)
      , rhs (rhs)
      , super ("pow", {rhs, lhs}, line, column) { }
  ExpressionPtr lhs, rhs;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*, Resolver&) override;
  ElementPtr    optimal ( ) override;
};

class Eq : public SpecializedExpression {
  public:
  Eq (ExpressionPtr lhs, ExpressionPtr rhs, u32 line, u32 column)
      : lhs (lhs)
      , rhs (rhs)
      , super ("eq", {rhs, lhs}, line, column) { }
  ExpressionPtr lhs, rhs;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*, Resolver&) override;
  ElementPtr    optimal ( ) override;
};

class Nand : public SpecializedExpression {
  public:
  Nand (ExpressionPtr lhs, ExpressionPtr rhs, u32 line, u32 column)
      : lhs (lhs)
      , rhs (rhs)
      , super ("nand", {rhs, lhs}, line, column) { }
  ExpressionPtr lhs, rhs;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*, Resolver&) override;
  ElementPtr    optimal ( ) override;
};

class Le : public SpecializedExpression {
  public:
  Le (ExpressionPtr lhs, ExpressionPtr rhs, u32 line, u32 column)
      : lhs (lhs)
      , rhs (rhs)
      , super ("le", {rhs, lhs}, line, column) { }
  ExpressionPtr lhs, rhs;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*, Resolver&) override;
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
      , super ("if", {cond, ifTrue, ifFalse}, line, column) { }
  ExpressionPtr cond, ifTrue, ifFalse;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*, Resolver&) override;
  ElementPtr    optimal ( ) override;
};

class Sqrt : public SpecializedExpression {
  public:
  Sqrt (ExpressionPtr value, u32 line, u32 column)
      : value (value)
      , super ("sqrt", {value}, line, column){ };
  ExpressionPtr value;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*, Resolver&) override;
  ElementPtr    optimal ( ) override;
};

class Sin : public SpecializedExpression {
  public:
  Sin (ExpressionPtr value, u32 line, u32 column)
      : value (value)
      , super ("sin", {value}, line, column){ };
  ExpressionPtr value;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*, Resolver&) override;
  ElementPtr    optimal ( ) override;
};

class Cos : public SpecializedExpression {
  public:
  Cos (ExpressionPtr value, u32 line, u32 column)
      : value (value)
      , super ("cos", {value}, line, column){ };
  ExpressionPtr value;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*, Resolver&) override;
  ElementPtr    optimal ( ) override;
};

class List : public SpecializedExpression {
  public:
  List (std::list<ExpressionPtr>& values, u32 line, u32 column)
      : values (values)
      , super ("list", values, line, column){ };
  List (std::list<ExpressionPtr>&& values, u32 line, u32 column)
      : values (values)
      , super ("list", values, line, column){ };
  std::list<ExpressionPtr> values;
  void                     print (std::ostream*) override;
  void                     compile (VM::Chunk*, Resolver&) override;
  ElementPtr               optimal ( ) override;
  void                     unfurl (VM::Chunk*             chunk,
                                   Resolver&              resolver,
                                   ASTPointer<Identifier> fun,
                                   VM::OpCode             code) {
    for (auto& i : values) {
      i->compile (chunk, resolver);
      chunk->write (VM::OP_BIND_NUMBER, {line, column});
      chunk->write (VM::OP_CALL, {line, column});
      fun->compile (chunk, resolver);
      if (code == VM::OP_FILTER) {
        chunk->write (VM::OP_JZ, {line, column});
        chunk->write (0xff, {line, column});
        u32 offset = chunk->write (0xff, {line, column}) - 2;
        chunk->write (VM::OP_POP, {line, column});
        i->compile (chunk, resolver);
        u32 endOfJump = chunk->getSize ( ) - offset;
        if (endOfJump > UINT16_MAX) {
          throw std::runtime_error ("Attempt to jump over too much code.");
        }

        chunk->storage[offset + 1] = (endOfJump >> 8) & 0xff;
        chunk->storage[offset + 2] = endOfJump & 0xff;
        chunk->write (VM::OP_JMP, {line, column});
        chunk->write (0xff, {line, column});
        offset = chunk->write (0xff, {line, column}) - 2;
        chunk->write (VM::OP_POP, {line, column});
        u32 jumpOutside = chunk->getSize ( ) - offset - 3;
        if (jumpOutside > UINT16_MAX) {
          throw std::runtime_error ("Attempt to jump over too much code.");
        }
        chunk->storage[offset + 1] = (jumpOutside >> 8) & 0xff;
        chunk->storage[offset + 2] = jumpOutside & 0xff;
      }
    }
    chunk->write (VM::OP_LIST_ALL, {line, column});
  }
};

using ListPtr = ASTPointer<List>;

class Head : public SpecializedExpression {
  public:
  Head (ListPtr value, u32 line, u32 column)
      : value (value)
      , super ("head", {value}, line, column){ };
  ListPtr    value;
  void       print (std::ostream*) override;
  void       compile (VM::Chunk*, Resolver&) override;
  ElementPtr optimal ( ) override;
};

class Tail : public SpecializedExpression {
  public:
  Tail (ListPtr value, u32 line, u32 column)
      : value (value)
      , super ("tail", {value}, line, column){ };
  ListPtr    value;
  void       print (std::ostream*) override;
  void       compile (VM::Chunk*, Resolver&) override;
  ElementPtr optimal ( ) override;
};

class Map : public SpecializedExpression {
  public:
  Map (IdentifierPtr funname, ListPtr list, u32 line, u32 column)
      : funname (funname)
      , list (list)
      , super ("map", {funname, list}, line, column) { }
  IdentifierPtr funname;
  ListPtr       list;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*, Resolver&) override;
  ElementPtr    optimal ( ) override;
};

class Filter : public SpecializedExpression {
  public:
  Filter (IdentifierPtr funname, ListPtr list, u32 line, u32 column)
      : funname (funname)
      , list (list)
      , super ("filter", {funname, list}, line, column) { }
  IdentifierPtr funname;
  ListPtr       list;
  void          print (std::ostream*) override;
  void          compile (VM::Chunk*, Resolver&) override;
  ElementPtr    optimal ( ) override;
};

}     // namespace ThisFunc::AST

#endif /* EXTENDEDAST_H */
