#include <ThisFunc/Token.hpp>


namespace ThisFunc {
  const std::string tokenTypeToString(TokenType t){
    switch(t){
    case TokenType::IDENTIFIER:
      return "Identifier";
    case TokenType::PARAM:
      return "Parameter";
    case TokenType::NUMBER:
      return "Number";
    case TokenType::LEFT_PAREN:
      return "Left Paren";
    case TokenType::RIGHT_PAREN:
      return "Right Paren";
    case TokenType::COMMA:
      return "Comma";
    case TokenType::ARROW_LEFT:
      return "Arrow Left";
    case TokenType::ERROR:
      return "Error";
    case TokenType::TOKEN_EOF:
      return "EOF";
    }
  }
}
