#include <ThisFunc/AST.hpp>
#include <iostream>

namespace ThisFunc::AST {

  void Identifier::print(){
    std::cout<<identifier;
  }

  ElementPtr Identifier::optimal() {
    return std::make_shared<Identifier>(*this);
  }

}
