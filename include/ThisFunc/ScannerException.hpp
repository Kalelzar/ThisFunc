#ifndef SCANNEREXCEPTION_H
#define SCANNEREXCEPTION_H

#include <exception>
#include <string>

namespace ThisFunc {

class ScannerException : public std::exception {
  public:
  ScannerException (std::string& msg) : msg (msg) { }
  ScannerException (std::string&& msg) : msg (std::move (msg)) { }

  private:
  std::string msg;
};

}     // namespace ThisFunc

#endif /* SCANNEREXCEPTION_H */
