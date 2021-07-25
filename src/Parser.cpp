#include <ThisFunc/AST.hpp>
#include <ThisFunc/Parser.hpp>
#include <ThisFunc/Scanner.hpp>

#include <iostream>
#include <sstream>

namespace ThisFunc {

AST::BodyPtr Parser::parse() {
  advance();
  auto b = body();
  consume(TokenType::TOKEN_EOF, "Expected end of expression");
  if (hadError)
    return nullptr;
  return b;
}

void Parser::advance() {
  previous = current;
  for (;;) {
    current = scanner.scan();
    // std::clog << "Current: [" << tokenTypeToString(current.type) << "] '"
    //           << current.lexeme << "' at " << current.line << ":"
    //           << current.column << std::endl;
    if (current.type != TokenType::ERROR)
      break;

    emitError();
  }
}

void Parser::emitError() {
  if (panicMode)
    return;
  std::ostringstream formatter;
  formatter << "LexerError: '" << current.lexeme << "' ("
            << tokenTypeToString(current.type) << ") at " << current.line << ":"
            << current.column << ".";
  std::cerr << formatter.str() << std::endl;
  hadError = true;
  panicMode = true;
}

void Parser::error(std::string message) { error(current, message); }

void Parser::error(Token target, std::string message) {
  if (panicMode)
    return;
  std::ostringstream formatter;
  formatter << "ParserError: '" << message << " " << target.lexeme << "' ("
            << tokenTypeToString(target.type) << ") at " << target.line << ":"
            << target.column << ".";
  std::cerr << formatter.str() << std::endl;
  hadError = true;
  panicMode = true;
}

bool Parser::consume(TokenType type, std::string message) {
  if (current.type != type) {
    error(message);
    return false;
  }
  advance();
  return true;
}

bool Parser::matches(TokenType type) {
  if (current.type != type) {
    return false;
  }
  return true;
}

bool Parser::isAtEnd() {
  if (current.type == TokenType::TOKEN_EOF) {
    return true;
  }
  return false;
}

AST::BodyPtr Parser::body() {
  std::list<AST::StatementPtr> statements;
  while (!isAtEnd()) {
    statements.push_back(statement());
  }
  return std::make_shared<AST::Body>(std::move(statements));
}

AST::StatementPtr Parser::statement() {
  if (matches(TokenType::IDENTIFIER)) {
    // Can still be a function call
    advance();

    auto identifier =
        std::make_shared<AST::Identifier>(std::move(previous.lexeme));
    if (matches(TokenType::ARROW_LEFT)) {
      // This is a function definition
      return fundef(identifier);
    } else {
      return funcall(identifier);
    }
  }

  return expression();
}

AST::FundefPtr Parser::fundef(AST::IdentifierPtr name) {
  consume(TokenType::ARROW_LEFT, "Expected '<-', found");
  auto functionDefinition = expression();
  return std::make_shared<AST::Fundef>(name, functionDefinition);
}

AST::FuncallPtr Parser::funcall(AST::IdentifierPtr name) {
  consume(TokenType::LEFT_PAREN, "Expected '(', found");
  std::list<AST::ExpressionPtr> args;
  while (!isAtEnd() && !matches(TokenType::RIGHT_PAREN)) {
    auto expr = expression();
    args.push_back(expr);
    if (matches(TokenType::RIGHT_PAREN))
      break;
    advance();
    if (!matches(TokenType::RIGHT_PAREN) && previous.type != TokenType::COMMA) {
      error(previous, "Expected ',', found");
    }
  }

  consume(TokenType::RIGHT_PAREN, "Expected ')', found");

  return std::make_shared<AST::Funcall>(name, std::move(args));
}

AST::ExpressionPtr Parser::expression() {

  if (matches(TokenType::NUMBER)) {
    return number();
  } else if (consume(TokenType::IDENTIFIER, "Expected an expression, found")) {
    auto identifier =
        std::make_shared<AST::Identifier>(std::move(previous.lexeme));
    if(matches(TokenType::LEFT_PAREN)){
      return funcall(identifier);
    }else{
      return identifier;
    }
  } else {
    advance();
    return std::make_shared<AST::Number>(69.69);
  }
}

AST::NumberPtr Parser::number() {
  consume(TokenType::NUMBER, "Expected number, found");
  double value = stod(previous.lexeme);

  return std::make_shared<AST::Number>(value);
}

} // namespace ThisFunc
