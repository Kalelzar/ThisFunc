#ifndef TOKEN_H
#define TOKEN_H

#include "defs.hpp"
#include <string>

namespace ThisFunc {

/**
 * An enum that describes the different types of ThisFunc::Token.
 */
enum class TokenType {

  /// Atoms
  IDENTIFIER, //< A function name. Can contain _#A-Za-z0-9 but cannot start with
              //0-9.
  NUMBER, //< A real number.

  /// Grammar

  LEFT_PAREN,  //< The '(' symbol.
  RIGHT_PAREN, //< The ')' symbol.

  COMMA,     //< The ',' symbol.
  ARROW_LEFT, //< The string "<-".

  ERROR,
  TOKEN_EOF,
};

struct Token {
  std::string lexeme;
  TokenType type;
  u32 line;
  u32 column;
};

  const std::string tokenTypeToString(TokenType t);

} // namespace ThisFunc

#endif /* TOKEN_H */
