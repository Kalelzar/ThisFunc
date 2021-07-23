#include <ThisFunc/AST.hpp>



#include <iostream>


namespace ThisFunc::AST {

  void Body::print(){
    for(auto& s : statements){
      s->print();
      std::cout<<std::endl;
    }
  }

  ElementPtr Body::optimal(){
    std::list<StatementPtr> newStatements;
    for(auto& statement : statements){
      newStatements.push_back(ptr_cast<Statement>(statement->optimal()));
    }
    return make_shared<Body>(std::move(newStatements)) ;
  }

}
