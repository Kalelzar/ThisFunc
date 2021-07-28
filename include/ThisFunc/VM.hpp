#ifndef VM_H
#define VM_H

#define STACK_MAX 256

#include <ThisFunc/Chunk.hpp>


namespace ThisFunc::VM {

class VM {
  private:
  Chunk*    chunk;
  Byte*     instructionPointer;
  Byte*     start;
  Constant  stack[STACK_MAX];
  Constant* stackTop;

  void      push (Constant c);
  Constant  pop ( );

  bool      run ( );

  public:
  VM ( )
      : instructionPointer (nullptr)
      , start (nullptr)
      , stackTop (stack)
      , chunk (nullptr) { }

  bool interpret (Chunk* chunk);
};

}     // namespace ThisFunc::VM

#endif /* VM_H */
