#ifndef AST_H
#define AST_H

#include <ThisFunc/Chunk.hpp>
#include <list>
#include <memory>
#include <string>
#include <type_traits>

namespace ThisFunc {
namespace AST {

  template<class A> using ASTPointer = std::shared_ptr<A>;

  class Element {
    public:
    /**
     * @brief      Print the AST node to stdout
     *
     * @details    Uses a Lisp-like syntax.
     */
    void         print ( ) { print (&std::cout); }
    /**
     * @brief      Print the AST node to the provided std::ostream
     *
     * @details    Uses a Lisp-like syntax.
     */
    virtual void print (std::ostream*) = 0;

    virtual void compile (VM::Chunk*)  = 0;

    Element (u32 line, u32 column) : line (line), column (column) { }

    /**
     * @brief      Return an optimal version of the AST node
     */
    virtual ASTPointer<Element> optimal ( ) = 0;
    /// @brief Returns true if the instance is and instance of Number and false
    /// otherwise
    virtual bool                isNumber ( ) { return false; }
    /// @brief Returns true if the instance is and instance of Identifier and
    /// false otherwise
    virtual bool                isIdentifier ( ) { return false; }

    u32                         line, column;
  };

  template<class T>
  concept ASTElement = std::is_base_of_v<Element, T>;


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
  template<ASTElement A, ASTElement B>
  AST::ASTPointer<A> ptr_cast (AST::ASTPointer<B> b) {
    return std::static_pointer_cast<A> (b);
  }

  using ElementPtr = ASTPointer<Element>;

  class Statement : public Element {
    public:
    Statement (u32 line, u32 column) : Element (line, column) { }
  };

  using StatementPtr = ASTPointer<Statement>;

  class Expression : public Statement {
    public:
    using super = Expression;
    Expression (u32 line, u32 column) : Statement (line, column) { }
  };
  using ExpressionPtr = ASTPointer<Expression>;

  class Number : public Expression {
    public:
    Number (double number, u32 line, u32 column)
        : number (number)
        , super (line, column) { }

    double              number;
    void                print (std::ostream*) override;
    void                compile (VM::Chunk*) override;
    ASTPointer<Element> optimal ( ) override;
    bool                isNumber ( ) override { return true; }
  };

  using NumberPtr = ASTPointer<Number>;

  class Identifier : public Expression {
    public:
    Identifier (std::string&, u32 line, u32 column) = delete;
    Identifier (std::string&& identifier, u32 line, u32 column)
        : identifier (identifier)
        , super (line, column) { }

    void                print (std::ostream*) override;
    ASTPointer<Element> optimal ( ) override;
    void                compile (VM::Chunk*) override;
    std::string         identifier;
    bool                isIdentifier ( ) override { return true; }
  };

  using IdentifierPtr = ASTPointer<Identifier>;

  class Funcall : public Expression {
    public:
    Funcall (IdentifierPtr              name,
             std::list<ExpressionPtr>&& args,
             u32                        line,
             u32                        column)
        : name (name)
        , args (args)
        , super (line, column) { }

    IdentifierPtr            name;
    std::list<ExpressionPtr> args;
    void                     print (std::ostream*) override;
    void                     compile (VM::Chunk*) override;
    ASTPointer<Element>      optimal ( ) override;
  };

  using FuncallPtr = ASTPointer<Funcall>;

  class Fundef : public Statement {
    public:
    Fundef (IdentifierPtr name, ExpressionPtr body, u32 line, u32 column)
        : name (name)
        , body (body)
        , Statement (line, column) { }

    void                print (std::ostream*) override;
    ASTPointer<Element> optimal ( ) override;
    void                compile (VM::Chunk*) override;
    const u32           arity ( );
    IdentifierPtr       name;
    ExpressionPtr       body;
    private:
    bool cached = false;
    u32  _arity = 0;
  };

  using FundefPtr = ASTPointer<Fundef>;

  class Body : public Element {
    public:
    void       print (std::ostream*) override;
    ElementPtr optimal ( ) override;
    void       compile (VM::Chunk*) override;
    Body (std::list<StatementPtr>& statements, u32 line, u32 column)
        : statements (statements)
        , Element (line, column) { }
    Body (std::list<StatementPtr>&& statements, u32 line, u32 column)
        : statements (statements)
        , Element (line, column) { }
    std::list<StatementPtr> statements;
  };

  using BodyPtr = ASTPointer<Body>;

}     // namespace AST
}     // namespace ThisFunc

#endif /* AST_H */
