#include <iostream>

#include <ThisFunc/Parser.hpp>
#include <ThisFunc/Interpreter.hpp>

int main(){

  ThisFunc::Parser s(&std::cin);
  ThisFunc::AST::BodyPtr ptr =  s.parse();
  ThisFunc::Interpreter interpreter(ptr);
  ptr->print();
  interpreter.precalculate();
  //  interpreter.print();

  return 0;
}
