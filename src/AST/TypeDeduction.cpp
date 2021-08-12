#include <ThisFunc/AST.hpp>
#include <ThisFunc/AmbiguousTypeException.hpp>
#include <ThisFunc/ConflictingNameException.hpp>
#include <ThisFunc/ExtendedAST.hpp>
#include <ThisFunc/Resolver.hpp>
#include <ThisFunc/TypeDeduction.hpp>
#include <ThisFunc/UndeclaredFunctionException.hpp>
#include <cassert>
#include <cstdio>
#include <sstream>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <vector>

#ifndef NDEBUG
#  define LOG_TYPE "(DEDUCE) "
#endif

namespace ThisFunc::AST {

using StackTrace = std::stack<CodeContext, std::deque<CodeContext>>;
template<>
Function
  deduce<Statement> (ASTPointer<Statement> e, StackTrace& s, Resolver& r);
template<>
Function deduce<Expression> (ASTPointer<Expression>, StackTrace&, Resolver& r);
template<>
Function deduce<Fundef> (ASTPointer<Fundef> ptr, StackTrace& s, Resolver& r) {
  LOG ("Defun: ",
       ptr->name->identifier,
       " at ",
       ptr->line,
       ":",
       ptr->column,
       std::endl);
  s.push ({{ptr->line, ptr->column}, ptr->name->identifier});
  Function f   = *r.get (ptr->name->identifier);
  auto     res = deduce (ptr->body, s, r);
  Function fin = f.merge (res, s);
  if (ptr->body->isNumber ( )) {
    if (fin.returnType == UnknownT || fin.returnType == NumberT) {
      LOG ("  RETURN: ", "Number", std::endl);
      fin.returnType = NumberT;
    } else
      throw AmbiguousTypeException (s, fin.returnType, NumberT);
  } else if (ptr->body->isIdentifier ( )) {
    IdentifierPtr ident = ptr_cast<Identifier> (ptr->body);
    if (!ident->identifier.starts_with ("#")) {
      if (fin.returnType == UnknownT || fin.returnType == FunctionT) {
        LOG ("  RETURN: ", "Function", std::endl);
        fin.returnType = FunctionT;
      } else
        throw AmbiguousTypeException (s, fin.returnType, FunctionT);
    } else {
      LOG ("  RETURN: ", "Identity", std::endl);
    }
  }
  s.pop ( );
  return fin;
}
template<>
Function deduce<Number> (ASTPointer<Number> n, StackTrace& s, Resolver& r) {
  LOG ("Number: ", n->number, " at ", n->line, ":", n->column, std::endl);
  return { };
}

template<>
Function
  deduce<Identifier> (ASTPointer<Identifier> id, StackTrace& s, Resolver& r) {
  s.push ({{id->line, id->column}, id->identifier});
  if (id->identifier.starts_with ("#")) {
    u32 i;
    sscanf (id->identifier.c_str ( ), "#%d", &i);
    Function f{ };
    f.fill (i);
    f.arguments[i]->deduceAs (UnknownT, s);
    s.pop ( );
    return f;
  } else {
    s.pop ( );
    return { };
  }
}

template<>
Function deduce<Funcall> (ASTPointer<Funcall> f, StackTrace& s, Resolver& r) {
  LOG ("Funcall: ",
       f->name->identifier,
       " at ",
       f->line,
       ":",
       f->column,
       std::endl);
  s.push ({{f->line, f->column}, f->name->identifier});
  if (f->name->identifier.starts_with ("#")) {
    u32 i;
    sscanf (f->name->identifier.c_str ( ), "#%d", &i);
    Function ff{ };
    ff.fill (i);
    assert (ff.arguments.size ( ) >= i);
    ff.arguments[i]->deduceAs (FunctionT, s);
    LOG ("#", i, " is a Function", std::endl);
    s.pop ( );
    return ff;
  } else {
    u32  i     = 0;
    // FIXME: DO NOT DO THIS.
    auto ffptr = r.get (f->name->identifier);
    if (!ffptr) { throw UndeclaredFunctionException (s, f->name->identifier); }
    Function ff = *ffptr;
    for (auto& arg : f->args) {
      std::ostringstream ss;
      ss << "Argument " << i;
      s.push ({{arg->line, arg->column}, ss.str ( )});
      auto argf = deduce (arg, s, r);
      if (arg->isNumber ( )) {
        LOG ("#", i, " is a Number", std::endl);
        ff.arguments[i]->deduceAs (NumberT, s);
      } else if (arg->isIdentifier ( )) {
        IdentifierPtr ident = ptr_cast<Identifier> (arg);
        if (!ident->identifier.starts_with ("#")) {
          LOG ("#", i, " is a Function", std::endl);
          ff.arguments[i]->deduceAs (FunctionT, s);
        }
      } else if (arg->type ( ) == ASTType::Funcall) {
        if (argf.returnType != UnknownT) {
          LOG ("#", i, " is a ", argf.returnType, std::endl);
          ff.arguments[i]->deduceAs (argf.returnType, s);
        }
      }
      i++;
    }

    // Here we can calculate the return type based on
    // the return type of the called function
    s.pop ( );
    return ff;
  }
}

template<>
Function
  deduce<Expression> (ASTPointer<Expression> e, StackTrace& s, Resolver& r) {
  if (e->type ( ) == ASTType::Funcall) {
    return deduce (ptr_cast<Funcall> (e), s, r);
  } else if (e->type ( ) == ASTType::Identifier) {
    return deduce (ptr_cast<Identifier> (e), s, r);
  } else {
    return deduce (ptr_cast<Number> (e), s, r);
  }
}

template<>
Function deduce<Body> (ASTPointer<Body> e, StackTrace& s, Resolver& r) {
  s.push ({{0, 0}, "PROG"});
  for (auto& st : e->statements) { deduce (st, s, r); }
  s.pop ( );
  return { };
}

template<>
Function
  deduce<Statement> (ASTPointer<Statement> e, StackTrace& s, Resolver& r) {
  if (e->type ( ) == ASTType::Fundef) {
    return deduce (ptr_cast<Fundef> (e), s, r);
  } else
    return deduce (ptr_cast<Expression> (e), s, r);
}


Type Argument::deduceAs (Type deducedType, StackTrace& s) {
  if (deducedType == UnknownT) return deducedType;
  if (type != UnknownT && type != deducedType) {
    throw AmbiguousTypeException (s, type, deducedType);
  } else if (type == UnknownT) {
    type = deducedType;
    alertDependents ( );
  }
  return deducedType;
}

void Argument::deduceLater (std::shared_ptr<Argument> arg, StackTrace& s) {
  if (type != UnknownT) { arg->deduceAs (type, s); }
  dependents.push_front ({arg, s});
  arg->dependents.push_front ({std::make_shared<Argument> (*this), s});
}

void Argument::alertDependents ( ) {
  for (auto& arg : dependents) {
    std::get<0> (arg)->deduceAs (type, std::get<1> (arg));
  }
}

bool     Argument::isOfType (Type t) const noexcept { return t == type; }


Function Function::merge (const Function& other, StackTrace& s) const {
  Function f;
  if (other.name != "" && name != "" && other.name != name) {
    throw ConflictingNameException (s, name, other.name);
  } else if (other.name != "") {
    f.name = other.name;
  } else {
    f.name = name;
  }

  if (other.returnType != returnType && other.returnType != UnknownT
      && returnType != UnknownT) {
    throw AmbiguousTypeException (s, returnType, other.returnType);
  } else if (other.returnType != UnknownT) {
    f.returnType = other.returnType;
  } else {
    f.returnType = returnType;
  }

  f.pos       = pos;

  f.usage     = std::max (usage, other.usage);

  u32 minargs = std::min (arguments.size ( ), other.arguments.size ( ));
  u32 maxargs = std::max (arguments.size ( ), other.arguments.size ( ));

  for (u32 i = 0; i < minargs; i++) {
    arguments[i]->deduceAs (other.arguments[i]->type, s);
    f.arguments.push_back (arguments[i]);
  }

  for (u32 i = minargs; i < maxargs; i++) {
    if (arguments.size ( ) < other.arguments.size ( )) {
      f.arguments.push_back (other.arguments[i]);
    } else {
      f.arguments.push_back (arguments[i]);
    }
  }

  return f;
}

}     // namespace ThisFunc::AST
