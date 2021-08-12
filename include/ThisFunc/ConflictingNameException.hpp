#ifndef CONFLICTINGNAMEEXCEPTION_H
#define CONFLICTINGNAMEEXCEPTION_H

#include <Kal/defs.hpp>
#include <ThisFunc/TypeDeduction.hpp>
#include <exception>
#include <sstream>
#include <string>

class ConflictingNameException : public std::exception {

  private:
  std::string msg;

  public:
  ConflictingNameException (ThisFunc::AST::StackTrace trace,
                            std::string               expected,
                            std::string               got) {
    std::ostringstream ss;
    ss << "Function reports two names " << expected << " and " << got
       << std::endl;
    while (!trace.empty ( )) {
      ss << " at: " << trace.top ( ).context << ":"
         << trace.top ( ).filePos.line << ":" << trace.top ( ).filePos.column
         << std::endl;
      trace.pop ( );
    }
    ss << "This is a compiler error. Please file report at "
          "'https://github.com/Kalelzar/ThisFunc'.";
    msg = ss.str ( );
  }

  virtual const char* what ( ) const noexcept override { return msg.c_str ( ); }
};

#endif /* CONFLICTINGNAMEEXCEPTION_H */
