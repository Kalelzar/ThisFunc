#ifndef UNDECLAREDFUNCTIONEXCEPTION_H
#define UNDECLAREDFUNCTIONEXCEPTION_H

#include <Kal/defs.hpp>
#include <ThisFunc/TypeDeduction.hpp>
#include <exception>
#include <sstream>
#include <string>

class UndeclaredFunctionException : public std::exception {

  private:
  std::string msg;

  public:
  UndeclaredFunctionException (ThisFunc::AST::StackTrace trace,
                               std::string               function) {
    std::ostringstream ss;
    ss << "Attempt to call the undeclared function " << function << std::endl;
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

#endif /* UNDECLAREDFUNCTIONEXCEPTION_H */
