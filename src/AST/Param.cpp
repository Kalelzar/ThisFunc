#include <ThisFunc/AST.hpp>
#include <iostream>

namespace ThisFunc::AST {

  void Param::print(){
    std::cout<<identifier;
  }

  ElementPtr Param::optimal() {
    return std::make_shared<Param>(*this);
  }

}
