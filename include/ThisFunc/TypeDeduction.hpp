#ifndef TYPEDEDUCTION_H
#define TYPEDEDUCTION_H


#include <Kal/defs.hpp>
#include <ThisFunc/AST.hpp>
#include <ThisFunc/CodeLocation.hpp>
#include <ThisFunc/Resolver.hpp>
#include <algorithm>
#include <forward_list>
#include <memory>
#include <stack>
#include <vector>

namespace ThisFunc::AST {


struct CodeContext {
  VM::CodeLocation filePos;
  std::string      context;
};

using StackTrace = std::stack<CodeContext, std::deque<CodeContext>>;

class Argument {
  private:
  std::forward_list<std::tuple<std::shared_ptr<Argument>, StackTrace>>
    dependents;
  public:
  Type type;
  Argument (Type type) : type (type), dependents ({ }){ };
  Argument ( ) : type (UnknownT), dependents ({ }){ };

  Argument (Argument& other) : type (other.type) {
    if (&other != this) { dependents = other.dependents; }
  };

  bool      operator== (Argument& other) { return type == other.type; }

  Argument& operator= (Argument& other) noexcept {
    if (this != &other) {
      type       = other.type;
      dependents = other.dependents;
    }
    return *this;
  }

  Argument (Argument&& other) noexcept : type (other.type) {
    if (this != &other) { dependents = std::move (other.dependents); }
  };

  Argument& operator= (Argument&& other) noexcept {
    if (this != &other) {
      type       = other.type;
      dependents = std::move (other.dependents);
    }
    return *this;
  }


  void deduceLater (std::shared_ptr<Argument>, StackTrace&);
  Type deduceAs (Type, StackTrace&);
  bool isOfType (Type) const noexcept;
  void alertDependents ( );
};

class Function {
  public:
  using ArgList = std::vector<std::shared_ptr<Argument>>;
  std::string      name;
  VM::CodeLocation pos;
  Type             returnType;
  ArgList          arguments;
  Usage            usage;

  Function (std::string&&    name,
            VM::CodeLocation pos,
            Type             returnType,
            ArgList          arguments,
            Usage            usage)
      : name (std::move (name))
      , pos (pos)
      , returnType (returnType)
      , arguments (arguments)
      , usage (usage) { }

  Function ( ) {
    name       = "";
    pos        = {0, 0};
    returnType = UnknownT;
    arguments  = ArgList ( );
    usage      = None;
  }

  void fill (u32 count) {
    for (u32 i = arguments.size ( ); i <= count; i++) {
      arguments.push_back (std::make_shared<Argument> ( ));
      std::cout << arguments[i]->isOfType (UnknownT) << std::endl;
    }
  }

  Function merge (const Function& other, StackTrace& s) const;

  bool     operator== (Function& other) {
    if (name != other.name || returnType != other.returnType
        || arguments.size ( ) != other.arguments.size ( ))
      return false;

    for (u32 i = 0; i < arguments.size ( ); i++) {
      if (arguments[i] != other.arguments[i]) return false;
    }

    return true;
  }
};

template<ASTElement T>
Function deduce (ASTPointer<T>, StackTrace&, Resolver& r);

}     // namespace ThisFunc::AST

#endif /* TYPEDEDUCTION_H */
