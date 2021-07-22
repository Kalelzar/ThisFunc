#include <ThisFunc/AST.hpp>

#include <iostream>

namespace ThisFunc::AST {

  void Body::print(){
    for(auto& s : statements){
      s->print();
      std::cout<<std::endl;
    }
  }

}
