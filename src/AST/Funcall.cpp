#include <ThisFunc/AST.hpp>
#include <iostream>

namespace ThisFunc::AST {

void Funcall::print() {
  std::cout << "(";
  name->print();
  for (auto &arg : args) {
    std::cout << " ";
    arg->print();
  }
  std::cout << ")";
}

ElementPtr Funcall::optimal() {

  }

  std::list<ExpressionPtr> newArgs;

  for (auto &arg : args) {
    newArgs.push_back(ptr_cast<Expression>(arg->optimal()));
  }

  return std::make_shared<Funcall>(name, std::move(newArgs));
}

} // namespace ThisFunc::AST
