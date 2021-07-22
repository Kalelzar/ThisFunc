#include <ThisFunc/AST.hpp>
#include <iostream>

namespace ThisFunc::AST {

  void Fundef::print(){
    std::cout<<"(defun ";
    name->print();
    std::cout<<" ";
    body->print();
    std::cout<<")";
  }

}
