#include <ThisFunc/AST.hpp>

#include <iostream>

namespace ThisFunc::AST {

  void Number::print() {
    std::cout<<number;
  }

}
