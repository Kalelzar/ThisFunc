#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <istream>
#include <queue>
#include "Token.hpp"

namespace ThisFunc {

class Scanner {
public:
  Scanner(std::istream* input) : input(input) {}

  /**
   * @brief      Return the next token
   *
   * @details    Scan ahead in the file until a new token can be generated.
   *             This reads from the file on-demand. Whether this is buffered or
   *             not depends on the implementation of std::istream.
   *             May return an error in the form of an Token with TokenType of
   *             TokenType::Error.
   */
  Token scan();

private:

  std::istream* input;
  std::string buffer;
  u32 line = 0;
  u32 column = 0;

  /**
   * @brief      Create a token of the given type.
   *
   * @details    This moves the read buffer into the token.
   *
   * @param      type The type of the token
   *
   * @return     Token
   */
  Token makeToken(TokenType type);
  Token makeError(std::string const& message) const;
  Token makeErrorf(std::string const& message) const;
  Token makeError(std::string const&& message) const;

  /**
   * @brief      Return the next character from the stream.
   *
   * @details    Read the next character into the buffer and return it.
   */
  char next();

  /**
   * @brief      Same as next() but doesn't add read char to buffer.
   */
  void skip();

  /**
   * @brief      Return the previously consumed character from the stream.
   *
   * @details    Returns the last character of the buffer.
   */
  char prev() const;

  /**
   * @brief      Peek at the next character from the stream.
   */
  char peek() const noexcept;

  bool isAtEnd() const;
  bool match(char const& b);

  void eatWhitespace();

  Token number();
  Token identifier();

};

} // namespace ThisFunc

#endif /* SCANNER_H */
