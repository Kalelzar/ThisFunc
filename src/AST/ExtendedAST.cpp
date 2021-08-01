#include <ThisFunc/ExtendedAST.hpp>

ThisFunc::AST::IdentifierPtr ThisFunc::AST::SpecializedExpression::spec
  = std::make_shared<Identifier> ("spec", 0, 0);
