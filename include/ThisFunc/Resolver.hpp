#ifndef RESOLVER_H
#define RESOLVER_H

#include <Kal/defs.hpp>
#include <ThisFunc/AST.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#ifndef NDEBUG

#  define PARENS          ( )

#  define EXPAND(...)     EXPAND2 (EXPAND2 (EXPAND2 (EXPAND2 (__VA_ARGS__))))
#  define EXPAND4(...)    EXPAND3 (EXPAND3 (EXPAND3 (EXPAND3 (__VA_ARGS__))))
#  define EXPAND3(...)    EXPAND2 (EXPAND2 (EXPAND2 (EXPAND2 (__VA_ARGS__))))
#  define EXPAND2(...)    EXPAND1 (EXPAND1 (EXPAND1 (EXPAND1 (__VA_ARGS__))))
#  define EXPAND1(...)    __VA_ARGS__
#  define PRINT(MSG, ...) __VA_OPT__ (EXPAND (PRINT_HELPER (MSG, __VA_ARGS__)))
#  define PRINT_HELPER(MSG, ...)                                               \
    MSG __VA_OPT__ (PRINT_AGAIN PARENS (__VA_ARGS__))
#  define PRINT_AGAIN( ) << PRINT_HELPER
#  define LOG(MSG, ...)  std::cout << LOG_TYPE << PRINT (MSG, __VA_ARGS__)
#else
#  define LOG(MSG, ...)
#endif


namespace ThisFunc::AST {

class Callable {
  public:
  VM::Chunk chunk;
  u32       arity;

  Callable (VM::Chunk& chunk, u32 arity) : chunk (chunk), arity (arity) { }

  Callable (Callable&& other) {
    if (&other != this) {
      chunk = std::move (other.chunk);
      arity = other.arity;
    }
  }

  Callable (Callable const& other) {
    if (&other != this) {
      chunk = other.chunk;
      arity = other.arity;
    }
  }

  Callable& operator= (Callable&& other) {
    if (&other != this) {
      chunk = std::move (other.chunk);
      arity = other.arity;
    }
    return *this;
  }

  Callable& operator= (const Callable& other) {
    if (&other != this) {
      chunk = other.chunk;
      arity = other.arity;
    }
    return *this;
  }
};


enum Type { NumberT, ListT, FunctionT, UnknownT, AnyT };
enum Usage { Strong, Weak, None };

class Function;
class Argument;

class Resolver {
  private:
  template<Type returnType, Type... args> void builtin (std::string name);
  public:
  Resolver ( );
  template<ASTElement T> void resolve (ASTPointer<T> element);
  std::shared_ptr<Function>   get (std::string name);
  Callable*                   call (std::string name);
  Callable*                   call (u32 i) { return &bytecodeCache[i]; }
  private:
  std::unordered_map<std::string, std::shared_ptr<Function>> cache;
  std::vector<Callable>                                      bytecodeCache;
};


}     // namespace ThisFunc::AST


#endif /* RESOLVER_H */
