#include <ThisFunc/AST.hpp>
#include <ThisFunc/ExtendedAST.hpp>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <stdexcept>

namespace ThisFunc::AST {

void If::print (std::ostream* out) {
  *out << "(if ";
  cond->print (out);
  *out << " ";
  ifTrue->print (out);
  *out << " ";
  ifFalse->print (out);
  *out << ")";
}

ElementPtr If::optimal ( ) {
  ElementPtr newCond = cond->optimal ( );

  if (cond->isNumber ( )) {
    double eval = ptr_cast<Number> (cond)->number;
    if (std::fabs (eval) <= 1E-6) {
      return ifFalse->optimal ( );
    } else {
      return ifTrue->optimal ( );
    }
  }

  return std::make_shared<If> (ptr_cast<Expression> (newCond),
                               ptr_cast<Expression> (ifTrue->optimal ( )),
                               ptr_cast<Expression> (ifFalse->optimal ( )),
                               line,
                               column);
}

void If::compile (VM::Chunk* chunk, Resolver& resolver) {
  cond->compile (chunk, resolver);
  chunk->write (VM::OP_JZ, {ifTrue->line, ifTrue->column});
  chunk->write (0xff, {ifTrue->line, ifTrue->column});
  u32 offset = chunk->write (0xff, {ifTrue->line, ifTrue->column}) - 2;
  chunk->write (VM::OP_POP, {ifTrue->line, ifTrue->column});
  ifTrue->compile (chunk, resolver);
  u32 jumpToElse = chunk->getSize ( ) - offset;
  if (jumpToElse > UINT16_MAX) {
    throw std::runtime_error ("Attempt to jump over too much code.");
  }
  chunk->storage[offset + 1] = (jumpToElse >> 8) & 0xff;
  chunk->storage[offset + 2] = jumpToElse & 0xff;

  chunk->write (VM::OP_JMP, {ifFalse->line, ifFalse->column});
  chunk->write (0xff, {ifFalse->line, ifFalse->column});
  offset = chunk->write (0xff, {ifFalse->line, ifFalse->column}) - 2;
  chunk->write (VM::OP_POP, {ifFalse->line, ifFalse->column});
  ifFalse->compile (chunk, resolver);
  u32 jumpOutsideIf = chunk->getSize ( ) - offset - 3;
  if (jumpOutsideIf > UINT16_MAX) {
    throw std::runtime_error ("Attempt to jump over too much code.");
  }
  chunk->storage[offset + 1] = (jumpOutsideIf >> 8) & 0xff;
  chunk->storage[offset + 2] = jumpOutsideIf & 0xff;
}

}     // namespace ThisFunc::AST
