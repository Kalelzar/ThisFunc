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

  ElementPtr Fundef::optimal() {
    ExpressionPtr newBody = ptr_cast<Expression>(body->optimal());
    return std::make_shared<Fundef>(name, newBody);
  }



}
