#include <ThisFunc/AST.hpp>


std::ostream& ThisFunc::AST::operator<< (std::ostream&          out,
                                         ThisFunc::AST::ASTType t) {
  switch (t) {
    case ThisFunc::AST::ASTType::Element: out << "Element"; break;
    case ThisFunc::AST::ASTType::Expression: out << "Expression"; break;
    case ThisFunc::AST::ASTType::Statement: out << "Statement"; break;
    case ThisFunc::AST::ASTType::Fundef: out << "Defun"; break;
    case ThisFunc::AST::ASTType::Funcall: out << "Funcall"; break;
    case ThisFunc::AST::ASTType::Number: out << "Number"; break;
    case ThisFunc::AST::ASTType::Identifier: out << "Identifier"; break;
    case ThisFunc::AST::ASTType::Body: out << "Body"; break;
  }

  return out;
}
