#include "ThisFunc/Chunk.hpp"
#include <iostream>

#include <ThisFunc/Parser.hpp>
#include <ThisFunc/Interpreter.hpp>

#include <ThisFunc/VM.hpp>
#include <ThisFunc/Disassembler.hpp>
#include <ThisFunc/Compiler.hpp>

int main(){

  ThisFunc::VM::Chunk chunk;

  ThisFunc::Compiler compiler;


  if(compiler.compile(&std::cin, &chunk)){

    ThisFunc::VM::disassemble(chunk);

    ThisFunc::VM::VM vm;
    if(vm.interpret(&chunk)){
      return 0;
    }else {
      return 1;
    }
  }

  // ThisFunc::Parser s(&std::cin);
  // ThisFunc::AST::BodyPtr ptr =  s.parse();
  // if(s.hadError) return 1;
  // ThisFunc::Interpreter interpreter(ptr);
  // ptr->print();
  // interpreter.precalculate();
  // //  interpreter.print();

  return 2;
}
