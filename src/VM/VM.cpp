#include "ThisFunc/Chunk.hpp"
#include <ThisFunc/Disassembler.hpp>
#include <ThisFunc/VM.hpp>

namespace ThisFunc::VM {
bool VM::interpret(Chunk *chunk) {
  this->chunk = chunk;
  this->start = chunk->getStorage();
  this->instructionPointer = chunk->getStorage();

  return run();
}

void VM::push(Constant c) {
  *stackTop = c;
  stackTop++;
}

Constant VM::pop() {
  stackTop--;
  return *stackTop;
}

bool VM::run() {
#define READ_INSTRUCTION() (*instructionPointer++)
#define READ_CONSTANT() (chunk->getConstant(READ_INSTRUCTION()))

  for (;;) {
#ifndef NDEBUG
    std::cout << "            ";
    for (Constant *slot = stack; slot < stackTop; slot++) {
      std::cout << "[ ";
      value(*slot);
      std::cout << " ]";
    }
    std::cout << std::endl;
    instruction(*chunk, (u64)(instructionPointer - start));
#endif
    Byte instruction = READ_INSTRUCTION();
    switch (instruction) {
    case OP_CONSTANT: {
      Constant constant = READ_CONSTANT();
      push(constant);
      break;
    }
    case OP_RETURN: {
     return true;
    }
    case OP_PRINT: {
      value(pop());
      std::cout << std::endl;
      break;
    }
    case OP_ADD: {
      push(pop() + pop());
      break;
    }
    case OP_SUBTRACT: {
      push(pop() - pop());
      break;
    }
    case OP_MULTIPLY: {
      push(pop() * pop());
      break;
    }
    case OP_DIVIDE: {
      push(pop() / pop());
      break;
    }
    case NOOP:
      break;
    }
  }

  return true;
#undef READ_CONSTANT
#undef READ_INSTRUCTION
}
} // namespace ThisFunc::VM
