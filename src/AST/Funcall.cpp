#include <ThisFunc/AST.hpp>
#include <iostream>

namespace ThisFunc::AST {

  void Funcall::print(){
    std::cout<<"(";
    name->print();
    for(auto& arg : args){
      std::cout<<" ";
      arg->print();
    }
    std::cout<<")";
  }

}