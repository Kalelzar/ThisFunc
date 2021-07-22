#ifndef PARSER_H
#define PARSER_H

#include <ThisFunc/AST.hpp>
#include <ThisFunc/Scanner.hpp>

namespace ThisFunc {

  class Parser {
  public:
    Parser(std::istream* input) : scanner(input) {}

    AST::BodyPtr parse();
    bool hadError = false;
  private:

    void advance();
    void emitError();
    void error(std::string message);
    void error(Token target, std::string message);
    bool consume(TokenType, std::string);
    bool matches(TokenType);
    bool isAtEnd();

    AST::BodyPtr body();
    AST::StatementPtr statement();
    AST::FundefPtr fundef(AST::IdentifierPtr);
    AST::FuncallPtr funcall(AST::IdentifierPtr);
    AST::ExpressionPtr expression();
    AST::NumberPtr number();
    AST::ParamExpressionPtr paramExpression();
    AST::ParamFuncallPtr paramFuncall();
    AST::ParamPtr param();

    Token previous = {};
    Token current = {};
    Scanner scanner;

    bool panicMode = false;
  };

}

#endif /* PARSER_H */
