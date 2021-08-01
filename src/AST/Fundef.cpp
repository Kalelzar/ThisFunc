#include <ThisFunc/AST.hpp>
#include <cmath>
#include <cstdio>
#include <iostream>

namespace ThisFunc::AST {

void Fundef::print (std::ostream* out) {
  *out << "\"\")\n(defun ";
  name->print (out);
  *out << " (";
  for (u32 i = 0; i < arity ( ); i++) {
    *out << "_" << i;
    if (i != arity ( ) - 1) *out << " ";
  }
  *out << ") ";
  body->print (out);
  *out << ")(progn";
}

template<ASTElement T> u32 walk (ASTPointer<T> t);
template<> u32             walk<Expression> (ExpressionPtr e);
template<> u32             walk<Number> (NumberPtr e) { return 0; }
template<> u32             walk<Identifier> (IdentifierPtr e) {
  if (e->identifier.starts_with ("#")) {
    u32 arity;
    sscanf (e->identifier.c_str ( ), "#%d", &arity);
    return arity + 1;
  } else {
    return 0;
  }
}
template<> u32 walk<Funcall> (FuncallPtr e) {
  u32 arity = walk (e->name);
  for (auto& element : e->args) { arity = std::max (arity, walk (element)); }
  return arity;
}
template<> u32 walk<Expression> (ExpressionPtr e) {
  if (e->isNumber ( ))
    return walk (ptr_cast<Number> (e));
  else if (e->isIdentifier ( ))
    return walk (ptr_cast<Identifier> (e));
  else
    return walk (ptr_cast<Funcall> (e));
}

const u32 Fundef::arity ( ) {
  if (cached) return _arity;
  _arity = walk (body);
  cached = true;
  return _arity;
}

ElementPtr Fundef::optimal ( ) {
  ExpressionPtr newBody = ptr_cast<Expression> (body->optimal ( ));
  return std::make_shared<Fundef> (name, newBody, line, column);
}

void Fundef::compile (VM::Chunk* chunk) {
  chunk->write (VM::NOOP, {line, column});
}

}     // namespace ThisFunc::AST
