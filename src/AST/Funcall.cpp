#include <ThisFunc/AST.hpp>
#include <ThisFunc/ExtendedAST.hpp>
#include <iostream>
#include <memory>

namespace ThisFunc::AST {

void Funcall::print (std::ostream* out) {
  *out << "(";
  name->print (out);
  for (auto& arg : args) {
    *out << " ";
    arg->print (out);
  }
  *out << ")";
}

void Funcall::compile (VM::Chunk* chunk) {
  chunk->write (VM::OP_CONSTANT, {line, column});
  chunk->write (chunk->addConstant (0), {line, column});
}

ElementPtr Funcall::optimal ( ) {
  if (name->identifier == "add" && args.size ( ) == 2) {
    auto add
      = std::make_shared<Add> (args.front ( ), args.back ( ), line, column)
          ->optimal ( );
    return add;
  } else if (name->identifier == "sub" && args.size ( ) == 2) {
    auto sub
      = std::make_shared<Sub> (args.front ( ), args.back ( ), line, column)
          ->optimal ( );
    return sub;
  } else if (name->identifier == "mul" && args.size ( ) == 2) {
    auto mul
      = std::make_shared<Mul> (args.front ( ), args.back ( ), line, column)
          ->optimal ( );
    return mul;
  } else if (name->identifier == "div" && args.size ( ) == 2) {
    auto div
      = std::make_shared<Div> (args.front ( ), args.back ( ), line, column)
          ->optimal ( );
    return div;
  } else if (name->identifier == "pow" && args.size ( ) == 2) {
    auto pow
      = std::make_shared<Pow> (args.front ( ), args.back ( ), line, column)
          ->optimal ( );
    return pow;
  } else if (name->identifier == "eq" && args.size ( ) == 2) {
    auto eq = std::make_shared<Eq> (args.front ( ), args.back ( ), line, column)
                ->optimal ( );
    return eq;
  } else if (name->identifier == "le" && args.size ( ) == 2) {
    auto le = std::make_shared<Le> (args.front ( ), args.back ( ), line, column)
                ->optimal ( );
    return le;
  } else if (name->identifier == "nand" && args.size ( ) == 2) {
    auto nand
      = std::make_shared<Nand> (args.front ( ), args.back ( ), line, column)
          ->optimal ( );
    return nand;
  } else if (name->identifier == "if" && args.size ( ) == 3) {
    return std::make_shared<If> (args.front ( ),
                                 *(++args.begin ( )),
                                 args.back ( ),
                                 line,
                                 column)
      ->optimal ( );
  } else if (name->identifier == "sqrt" && args.size ( ) == 1) {
    return std::make_shared<Sqrt> (args.front ( ), line, column)->optimal ( );
  } else if (name->identifier == "sin" && args.size ( ) == 1) {
    return std::make_shared<Sin> (args.front ( ), line, column)->optimal ( );
  } else if (name->identifier == "cos" && args.size ( ) == 1) {
    return std::make_shared<Cos> (args.front ( ), line, column)->optimal ( );
  } else if (name->identifier == "head" && args.size ( ) == 1) {
    // FIX: Check type before casting
    return std::make_shared<Head> (ptr_cast<List> (args.front ( )->optimal ( )),
                                   line,
                                   column)
      ->optimal ( );
  } else if (name->identifier == "tail" && args.size ( ) == 1) {
    // FIX: Check type before casting
    return std::make_shared<Tail> (ptr_cast<List> (args.front ( )->optimal ( )),
                                   line,
                                   column)
      ->optimal ( );
  } else if (name->identifier == "list") {
    return std::make_shared<List> (std::move (args), line, column);
  } else if (name->identifier == "map" && args.size ( ) == 2) {
    // FIX: Check type before casting
    auto map
      = std::make_shared<Map> (ptr_cast<Identifier> (args.front ( )),
                               ptr_cast<List> (args.back ( )->optimal ( )),
                               line,
                               column)
          ->optimal ( );
    return map;
  }

  std::list<ExpressionPtr> newArgs;

  for (auto& arg : args) {
    newArgs.push_back (ptr_cast<Expression> (arg->optimal ( )));
  }

  return std::make_shared<Funcall> (name, std::move (newArgs), line, column);
}

}     // namespace ThisFunc::AST
