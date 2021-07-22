#include <ThisFunc/AST.hpp>
#include <iostream>

namespace ThisFunc::AST {

  void Identifier::print(){
    std::cout<<identifier;
  }

}
