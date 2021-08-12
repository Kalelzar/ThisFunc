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

template<int index, Type next, Type... args> struct initArgs {
  void act (Resolver* r, std::string name) {
    std::shared_ptr<Function> f = r->get (name);
    f->arguments[index]         = std::make_shared<Argument> (next);
    initArgs<index + 1, args...> ( ).act (r, name);
  }
};

template<int index, Type next> struct initArgs<index, next> {
  void act (Resolver* r, std::string name) { }
};

Resolver::Resolver ( ) { builtin<NumberT, NumberT, NumberT> ("spec"); }

template<Type returnType, Type... args>
void Resolver::builtin (std::string name) {
  std::string namecp = name;
  cache.emplace (name,
                 std::make_shared<Function,
                                  std::string,
                                  VM::CodeLocation,
                                  Type,
                                  std::vector<std::shared_ptr<Argument>>,
                                  Usage> (
                   std ::move (namecp),
                   {0, 0},
                   returnType,
                   std::vector<std::shared_ptr<Argument>> (sizeof...(args)),
                   Strong));
  initArgs<0, args...> ( ).act (this, name);
}


}     // namespace ThisFunc::AST
