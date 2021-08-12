#ifndef AMBIGUOUSTYPEEXCEPTION_H
#define AMBIGUOUSTYPEEXCEPTION_H

#include <Kal/defs.hpp>
#include <ThisFunc/TypeDeduction.hpp>
#include <exception>
#include <sstream>
#include <string>

class AmbiguousTypeException : public std::exception {

  private:
  std::string msg;

  public:
  AmbiguousTypeException (ThisFunc::AST::StackTrace trace,
                          ThisFunc::AST::Type       expected,
                          ThisFunc::AST::Type       got) {
    std::ostringstream ss;
    ss << "Expected a " << expected << " where a " << got << " was given "
       << std::endl;
    while (!trace.empty ( )) {
      ss << " at: " << trace.top ( ).context << ":"
         << trace.top ( ).filePos.line << ":" << trace.top ( ).filePos.column
         << std::endl;
      trace.pop ( );
    }
    msg = ss.str ( );
  }

  virtual const char* what ( ) const noexcept override { return msg.c_str ( ); }
};

#endif /* AMBIGUOUSTYPEEXCEPTION_H */
