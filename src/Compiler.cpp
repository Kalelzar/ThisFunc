#include <ThisFunc/AST.hpp>
#include <ThisFunc/Compiler.hpp>
#include <ThisFunc/Resolver.hpp>
#include <ThisFunc/TypeDeduction.hpp>

namespace ThisFunc {
bool Compiler::compile (std::istream* in, VM::Chunk* bytecode) {
  Parser        parser (in);
  AST::BodyPtr  result = parser.parse ( );

  AST::Resolver r;

  if (parser.hadError) {
    std::cerr << "Compilation unsuccessful." << std::endl;
    return false;
  }

  auto opt = AST::ptr_cast<AST::Body> (result->optimal ( ));
  opt->print (&std::cout);
  r.resolve (opt);
  AST::StackTrace s;
  AST::deduce (opt, s, r);
  opt->compile (bytecode);

  return true;
}
}     // namespace ThisFunc
