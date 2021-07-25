#include "ThisFunc/AST.hpp"
#include <ThisFunc/ExtendedAST.hpp>

#include <iostream>
#include <cmath>
#include <string>

namespace ThisFunc::AST {

void Eq::print() {
  std::cout << "(= ";
  lhs->print();
  std::cout << " ";
  rhs->print();
  std::cout << ")";
}

ElementPtr Eq::optimal() {
  ElementPtr nlhs = lhs->optimal();
  ElementPtr nrhs = rhs->optimal();

  if (nlhs->isNumber() && nrhs->isNumber()) {
    double lhsd = ptr_cast<Number>(nlhs)->number;
    double rhsd = ptr_cast<Number>(nrhs)->number;
    return std::make_shared<Number>(std::fabs(lhsd - rhsd) < 1E-6 ? 1 : 0);
  }else if(nlhs->isIdentifier() && nrhs->isIdentifier()){
    std::string lhss = ptr_cast<Identifier>(nlhs)->identifier;
    std::string rhss = ptr_cast<Identifier>(nrhs)->identifier;
    if(lhss == rhss)
      return std::make_shared<Number>(1);
  }
  return std::make_shared<Eq>(ptr_cast<Expression>(nlhs),
                               ptr_cast<Expression>(nrhs));
}

} // namespace ThisFunc::AST
