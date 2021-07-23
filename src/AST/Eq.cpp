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
  }else if(nlhs->isParameter() && nrhs->isParameter()){
    std::string lhss = ptr_cast<Param>(nlhs)->identifier;
    std::string rhss = ptr_cast<Param>(nrhs)->identifier;
    return std::make_shared<Number>(lhss == rhss ? 1 : 0);
  }
  return std::make_shared<Eq>(ptr_cast<Expression>(nlhs),
                               ptr_cast<Expression>(nrhs));
}

} // namespace ThisFunc::AST
