#include <ThisFunc/Compiler.hpp>
#include <ThisFunc/VM.hpp>
#include <cassert>
#include <fstream>
#include <hayai/hayai.hpp>

bool executeTF (std::string filename) {
  std::ifstream       file (filename);
  ThisFunc::VM::Chunk chunk;

  ThisFunc::Compiler  compiler;

  if (compiler.compile (&file, &chunk)) {
    //    ThisFunc::VM::disassemble(chunk);

    ThisFunc::VM::VM vm;
    if (vm.interpret (&chunk)) {
      return true;
    } else {
      return false;
    }
  }

  return false;
}

BENCHMARK (ThisFunc, Numeric_Expression, 20, 1) {
  assert (executeTF ("benchmarks/numexpr.tf"));
}

BENCHMARK (ThisFunc, Add, 20, 1) { assert (executeTF ("benchmarks/add.tf")); }
