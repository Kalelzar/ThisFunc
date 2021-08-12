#include "ThisFunc/CodeLocation.hpp"

#include <ThisFunc/Resolver.hpp>
#include <ThisFunc/TypeDeduction.hpp>
#include <memory>

#ifndef NDEBUG
#  define LOG_TYPE "(RESOLVE) "
#endif

namespace ThisFunc::AST {

template<> void Resolver::resolve<Fundef> (FundefPtr fundef) {
  std::string temp = fundef->name->identifier;
  LOG ("Defun: ",
       fundef->name->identifier,
       " with arity of ",
       fundef->arity ( ),
       std::endl);
  auto func = std::make_shared<Function,
                               std::string,
                               VM::CodeLocation,
                               Type,
                               std::vector<std::shared_ptr<Argument>>,
                               Usage> (
    std::move (temp),
    {fundef->line, fundef->column},
    UnknownT,
    std::vector<std::shared_ptr<Argument>> (fundef->arity ( )),
    None);

  for (u32 i = 0; i < fundef->arity ( ); i++) {
    func->arguments[i] = std::make_shared<Argument> ( );
  }
  VM::Chunk c;
  bytecodeCache.push_back ({c, fundef->arity ( )});
  u32 ind     = bytecodeCache.size ( ) - 1;
  func->index = ind;
  cache.emplace (fundef->name->identifier, func);
}

template<> void Resolver::resolve<Statement> (StatementPtr element) {
  LOG ("Stmt: ", element->type ( ), std::endl);
  if (element->type ( ) == ASTType::Fundef) {
    resolve (ptr_cast<Fundef> (element));
  }
}

template<> void Resolver::resolve<Body> (BodyPtr element) {
  LOG ("Body: ", element->statements.size ( ), " Statements", std::endl);
  for (auto& statement : element->statements) { resolve (statement); }
}

template<> void Resolver::resolve<Element> (ElementPtr element) {
  LOG ("Element: ", element->type ( ), std::endl);
}

std::shared_ptr<Function> Resolver::get (std::string name) {
  return cache[name];
}


template<int index, Type... args> struct initArgs {
  void act (Resolver*, std::string);
};

template<int index, Type next, Type... args>
struct initArgs<index, next, args...> {
  void act (Resolver* r, std::string name) {
    LOG (name, " initialize argument ", index, " ", next, std::endl);
    std::shared_ptr<Function> f = r->get (name);
    f->arguments[index]         = std::make_shared<Argument> (next);
    initArgs<index + 1, args...> ( ).act (r, name);
  }
};

template<int index> struct initArgs<index> {
  void act (Resolver* r, std::string name) { }
};

Resolver::Resolver ( ) {
  builtin<NumberT, NumberT, NumberT> ("add");
  builtin<NumberT, NumberT, NumberT> ("sub");
  builtin<NumberT, NumberT, NumberT> ("mul");
  builtin<NumberT, NumberT, NumberT> ("div");
  builtin<NumberT, NumberT, NumberT> ("pow");
  builtin<AnyT, NumberT, AnyT, AnyT> ("if");
  builtin<NumberT, NumberT, NumberT> ("eq");
  builtin<NumberT, NumberT, NumberT> ("le");
  builtin<NumberT, NumberT> ("nand");
  builtin<NumberT, NumberT> ("sqrt");
  builtin<NumberT, NumberT> ("sin");
  builtin<NumberT, NumberT> ("cos");
  builtin<ListT, NumberT> ("list");
  builtin<AnyT, ListT> ("head");
  builtin<ListT, ListT> ("tail");
  builtin<ListT, FunctionT, ListT> ("map");
  builtin<ListT, FunctionT, ListT> ("filter");
}

template<Type returnType, Type... args>
void Resolver::builtin (std::string name) {
  std::string namecp = name;
  VM::Chunk   c;
  u32         arity = sizeof...(args);
  bytecodeCache.push_back ({c, arity});
  u32  ind = bytecodeCache.size ( ) - 1;
  auto func
    = std::make_shared<Function,
                       std::string,
                       VM::CodeLocation,
                       Type,
                       std::vector<std::shared_ptr<Argument>>,
                       Usage> (std ::move (namecp),
                               {0, 0},
                               returnType,
                               std::vector<std::shared_ptr<Argument>> (arity),
                               Strong);
  func->index = ind;
  cache.emplace (name, func);
  initArgs<0, args...> ( ).act (this, name);
}

Callable* Resolver::call (std::string name) {
  return &bytecodeCache[(get (name)->index)];
}


}     // namespace ThisFunc::AST
