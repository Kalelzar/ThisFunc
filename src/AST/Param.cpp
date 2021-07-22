#include <ThisFunc/AST.hpp>
#include <iostream>

namespace ThisFunc::AST {

  void Param::print(){
    std::cout<<identifier;
  }

}
