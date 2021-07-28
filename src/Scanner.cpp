#include <ThisFunc/Scanner.hpp>
#include <ThisFunc/ScannerException.hpp>
#include <sstream>

namespace ThisFunc {

Token Scanner::makeToken (TokenType type) {
  u32   length = buffer.length ( );
  Token t{std::move (buffer), type, line, column};
  column += length;
  buffer = std::string ( );
  return t;
}

Token Scanner::makeError (std::string const& message) const {
  return {message, TokenType::ERROR, line, column};
}

Token Scanner::makeError (std::string const&& message) const {
  return {std::move (message), TokenType::ERROR, line, column};
}

Token Scanner::makeErrorf (std::string const& msg) const {
  std::ostringstream message;
  message << msg << " '" << buffer << "'";
  return {message.str ( ), TokenType::ERROR, line, column};
}

inline bool isValidForIdentifier (char c) {
  return std::isalnum (c) || c == '_';
}

Token Scanner::scan ( ) {
  eatWhitespace ( );
  switch (next ( )) {
    case '<':
      if (match ('-')) {
        return makeToken (TokenType::ARROW_LEFT);
      } else {
        return makeError ("Malformed '<-' operator");
      }
      break;
    case '(': return makeToken (TokenType::LEFT_PAREN); break;
    case ')': return makeToken (TokenType::RIGHT_PAREN); break;
    case ',': return makeToken (TokenType::COMMA); break;
    case '#': return identifier ( ); break;
    case '\0': return makeToken (TokenType::TOKEN_EOF);
    default:
      if ((prev ( ) == '-' && std::isdigit (peek ( )))
          || std::isdigit (prev ( ))) {
        return number ( );
      } else {
        if (isValidForIdentifier (prev ( ))) {
          return identifier ( );
        } else {
          return makeErrorf ("Unrecognized character");
        }
      }
  }
}

char Scanner::next ( ) {
  if (isAtEnd ( )) { return '\0'; }

  char c = input->get ( );
  buffer.push_back (c);
  return c;
}

char Scanner::peek ( ) const noexcept {
  if (isAtEnd ( )) { return '\0'; }

  return input->peek ( );
};

char Scanner::prev ( ) const {
  if (buffer.empty ( )) {
    throw ScannerException ("Calling prev() with an empty buffer.");
  }

  return buffer.back ( );
}

bool Scanner::isAtEnd ( ) const { return input->eof ( ); }

bool Scanner::match (char const& b) {
  if (isAtEnd ( ) || peek ( ) != b) { return false; }
  next ( );
  return true;
}

void Scanner::skip ( ) {
  if (isAtEnd ( )) { return; }

  input->get ( );
}

void Scanner::eatWhitespace ( ) {
  for (;;) {
    switch (peek ( )) {
      case '\n':
        column = 0;
        line++;
        skip ( );
        break;
      case ' ':
      case '\r':
      case '\t':
        column++;
        skip ( );
        break;
      default: return;
    }
  }
}

Token Scanner::number ( ) {
  for (;;) {
    char c = peek ( );
    if (isdigit (c)) {
      next ( );
    } else
      break;
  }
  if (match ('.')) {
    for (;;) {
      char c = peek ( );
      if (isdigit (c)) {
        next ( );
      } else
        break;
    }
  }
  if (match ('.')) {
    return makeError ("Malformed numeric literal. Multiple '.' found.");
  }
  return makeToken (TokenType::NUMBER);
}

Token Scanner::identifier ( ) {
  for (;;) {
    char c = peek ( );
    if (isValidForIdentifier (c) || c == '.') {
      next ( );
    } else {
      return makeToken (TokenType::IDENTIFIER);
    }
  }
}

}     // namespace ThisFunc
