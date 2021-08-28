#include "ThisFunc/AST.hpp"

#include <ThisFunc/Chunk.hpp>
#include <ThisFunc/Disassembler.hpp>
#include <ThisFunc/VM.hpp>
#include <cmath>
#include <stdexcept>

namespace ThisFunc::VM {
bool VM::interpret (Chunk* chunk, AST::Resolver r) {
  frames[frameCount] = {0, chunk};
  this->resolver     = r;

  return run ( );
}

void VM::push (Constant c, BoundType t) {
  *stackTop  = c;
  *tstackTop = t;
  tstackTop++;
  stackTop++;
}

Constant VM::peek (u32 at) {
  if (stackTop - at <= stack) {
    throw std::runtime_error ("Attempt to peek beyound the stack.");
  } else {
    return *(stackTop - at);
  }
}

Constant VM::pop ( ) {
  if (stackTop == stack) {
    throw std::runtime_error ("Popping an empty stack.");
  }
  stackTop--;
  tstackTop--;
  return *stackTop;
}

bool VM::run ( ) {
#define READ_INSTRUCTION( )                                                    \
  ((*frames[frameCount].chunk)[frames[frameCount].instructionPointer++])
#define READ_CONSTANT( )                                                       \
  (frames[frameCount].chunk->getConstant (READ_INSTRUCTION ( )))
#define READ_SHORT( )                                                          \
  (frames[frameCount].instructionPointer += 2,                                 \
   (u16) ((*frames[frameCount]                                                 \
              .chunk)[frames[frameCount].instructionPointer - 2]               \
            << 8                                                               \
          | (*frames[frameCount]                                               \
                .chunk)[frames[frameCount].instructionPointer - 1]))
  for (;;) {
#ifndef NDEBUG
    std::cout << "            ";
    for (u32 i = 0; i < frames[frameCount].boundCount; i++) {
      std::cout << "< ";
      value (frames[frameCount].binds[i].index);
      std::cout << " >";
    }
    std::cout << std::endl;
    std::cout << "            ";
    for (Constant* slot = stack; slot < stackTop; slot++) {
      std::cout << "[ ";
      value (*slot);
      std::cout << " ]";
    }
    std::cout << std::endl;
    instruction (*frames[frameCount].chunk,
                 (u64) (frames[frameCount].instructionPointer));
#endif
    if (frames[frameCount].instructionPointer
        > frames[frameCount].chunk->getSize ( )) {
      throw std::runtime_error ("Unexpected end of program.");
    }
    Byte instruction = READ_INSTRUCTION ( );
    switch (instruction) {
      case OP_CONSTANT: {
        Constant constant = READ_CONSTANT ( );
        push (constant, bNumber);
        break;
      }
      case OP_LIST: {
        std::forward_list<Constant> l;
        Byte                        elements = READ_INSTRUCTION ( );
        for (u8 i = 0; i < elements; i++) { l.push_front (pop ( )); }
        lists.push_back (std::move (l));
        push (lists.size ( ) - 1, bList);
        break;
      }
      case OP_LIST_ALL: {
        std::forward_list<Constant> l;
        while (stack != stackTop) { l.push_front (pop ( )); }
        lists.push_back (std::move (l));
        push (lists.size ( ) - 1, bList);
        break;
      }
      case OP_RETURN: {
        if (frameCount == 0) exit (0);
        frames[frameCount].boundCount = 0;
        frameCount--;
        break;
      }
      case OP_PRINT: {
        if (*(tstackTop - 1) == bNumber) {
          value (pop ( ));
        } else if (*(tstackTop - 1) == bList) {
          auto& t = lists[pop ( )];
          std::cout << "'(";
          for (auto& el : t) { std::cout << el << " "; }
          std::cout << ")";
        }
        std::cout << std::endl;
        break;
      }
      case OP_ADD: {
        push (pop ( ) + pop ( ), bNumber);
        break;
      }
      case OP_EQ: {
        push (pop ( ) == pop ( ) ? 1 : 0, bNumber);
        break;
      }
      case OP_NAND: {
        push (pop ( ) == 0 || pop ( ) == 0 ? 1 : 0, bNumber);
        break;
      }
      case OP_LE: {
        push (pop ( ) >= pop ( ) == 0 ? 1 : 0, bNumber);
        break;
      }
      case OP_SUBTRACT: {
        push (pop ( ) - pop ( ), bNumber);
        break;
      }
      case OP_MULTIPLY: {
        push (pop ( ) * pop ( ), bNumber);
        break;
      }
      case OP_DIVIDE: {
        push (pop ( ) / pop ( ), bNumber);
        break;
      }
      case OP_SIN: {
        push (std::sin (pop ( )), bNumber);
        break;
      }
      case OP_SQRT: {
        push (std::sqrt (pop ( )), bNumber);
        break;
      }
      case OP_COS: {
        push (std::cos (pop ( )), bNumber);
        break;
      }
      case OP_POW: {
        push (std::pow (pop ( ), pop ( )), bNumber);
        break;
      }
      case OP_JZ: {
        u16 jumpOffset = READ_SHORT ( );
        if (std::abs (*(stackTop - 1)) <= 1E-6)
          frames[frameCount].instructionPointer += jumpOffset;
        break;
      }
      case OP_JMP: {
        u16 jumpOffset = READ_SHORT ( );
        frames[frameCount].instructionPointer += jumpOffset;
        break;
      }
      case OP_POP: {
        pop ( );
        break;
      }
      case OP_LOAD: {
        u32        id = READ_INSTRUCTION ( );
        BoundValue bv = frames[frameCount].binds[id];
        push (bv.index, bv.type);
        break;
      }
      case OP_CALL: {
        u32   index            = READ_INSTRUCTION ( );
        auto* callable         = resolver.call (index);
        frames[frameCount + 1] = {0, &callable->chunk, binds, boundCount};
        boundCount             = 0;
        frameCount++;
        break;
      }
      case OP_BIND_NUMBER: {
        binds[boundCount] = {(u32) pop ( ), bNumber};
        boundCount++;
        break;
      }
      case OP_BIND_FUNCTION: {
        binds[boundCount] = {(u32) pop ( ), bFunction};
        boundCount++;
        break;
      }
      case OP_BIND_LIST: {
        binds[boundCount] = {(u32) pop ( ), bList};
        boundCount++;
        break;
      }
      case NOOP: break;
    }
  }

  return true;
#undef READ_CONSTANT
#undef READ_INSTRUCTION
#undef READ_SHORT
}     // namespace ThisFunc::VM


}     // namespace ThisFunc::VM
