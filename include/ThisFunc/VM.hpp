#ifndef VM_H
#define VM_H

#include "ThisFunc/Disassembler.hpp"
#define STACK_MAX 256

#include <ThisFunc/Chunk.hpp>
#include <ThisFunc/TypeDeduction.hpp>

namespace ThisFunc::VM {

enum BoundType { bFunction, bNumber, bList };

struct BoundValue {
  u32       index;
  BoundType type;
};

struct CallFrame {
  u32                         instructionPointer;
  Chunk*                      chunk;
  std::array<BoundValue, 256> binds;
  u32                         boundCount = 0;
};

class VM {
  private:
  CallFrame                                frames[STACK_MAX];
  u32                                      frameCount = 0;
  std::array<BoundValue, 256>              binds;
  u32                                      boundCount = 0;
  Constant                                 stack[STACK_MAX];
  Constant*                                stackTop;
  BoundType                                tstack[STACK_MAX];
  BoundType*                               tstackTop;
  std::vector<std::forward_list<Constant>> lists;
  AST::Resolver                            resolver;
  void                                     push (Constant c, BoundType t);
  Constant                                 pop ( );
  Constant                                 peek (u32 at);
  bool                                     run ( );

  public:
  VM ( ) : stackTop (stack), tstackTop (tstack), resolver ({ }) { }

  bool interpret (Chunk* chunk, AST::Resolver r);
};

}     // namespace ThisFunc::VM

#endif /* VM_H */
