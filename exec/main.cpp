#include <Kal/HashArray.hpp>
#include <ThisFunc/Chunk.hpp>
#include <ThisFunc/Compiler.hpp>
#include <ThisFunc/Disassembler.hpp>
#include <ThisFunc/Parser.hpp>
#include <ThisFunc/Resolver.hpp>
#include <ThisFunc/TypeDeduction.hpp>
#include <ThisFunc/VM.hpp>
#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>


int run (std::istream* stream) {
  ThisFunc::VM::Chunk chunk;

  ThisFunc::Compiler  compiler;

  ThisFunc::VM::VM    vm;
  if (vm.interpret (&chunk, compiler.compile (stream, &chunk))) {
    return 0;
  } else {
    return 1;
  }
}

int main (int argv, char** argc) {
  try {
    if (argv >= 2) {
      std::ifstream stream (argc[1]);
      return run (&stream);
    } else {
      std::cout << "Press ctrl-d in order to run the code you have written."
                << std::endl;
      return run (&std::cin);
    }
  } catch (std::runtime_error& e) {
    std::cerr << "Runtime Error: " << e.what ( ) << std::endl;
    return 3;
  }
}
