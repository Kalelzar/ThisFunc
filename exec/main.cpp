#include <iostream>

#include <ThisFunc/Parser.hpp>

int main(){

  ThisFunc::Parser s(&std::cin);
  s.parse()->print();
  return 0;
}
