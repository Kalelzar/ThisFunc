#include <ThisFunc/AST.hpp>
#include <iostream>
#include <unordered_set>

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

template<ASTElement T> std::unordered_set<std::string> walk (ASTPointer<T> t);
template<> std::unordered_set<std::string> walk<Expression> (ExpressionPtr e);
template<> std::unordered_set<std::string> walk<Number> (NumberPtr e) {
  return std::move (std::unordered_set<std::string> ( ));
}
template<> std::unordered_set<std::string> walk<Identifier> (IdentifierPtr e) {
  if (e->identifier.starts_with ("#")) {
    std::unordered_set<std::string> set;
    set.insert (e->identifier);
    return std::move (set);
  } else {
    return std::move (std::unordered_set<std::string> ( ));
  }
}
template<> std::unordered_set<std::string> walk<Funcall> (FuncallPtr e) {
  std::unordered_set<std::string> set = walk (e->name);
  for (auto& element : e->args) { set.merge (std::move (walk (element))); }
  return std::move (set);
}
template<> std::unordered_set<std::string> walk<Expression> (ExpressionPtr e) {
  if (e->isNumber ( ))
    return walk (ptr_cast<Number> (e));
  else if (e->isIdentifier ( ))
    return walk (ptr_cast<Identifier> (e));
  else
    return walk (ptr_cast<Funcall> (e));
}

const u32 Fundef::arity ( ) {
  if (cached) return _arity;

  std::unordered_set<std::string> set;
  set = walk (body);

  if (set.size ( ) == 0) {
    _arity = 0;
  } else {
    u32 max = 0;

    for (auto& e : set) {
      u32 index = atoi ((e.c_str ( ) + 1));
      if (max < index) max = index;
    }
    _arity = max + 1;
  }

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
