#include <ThisFunc/Scanner.hpp>

#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include <sstream>

RC_GTEST_PROP(Scanner, anIntegerIsScannedAsNumber, (const i32 num)){
  std::stringstream stream;
  stream << num;
  ThisFunc::Scanner scanner(&stream);

  ThisFunc::Token token = scanner.scan();

  RC_ASSERT(token.type == ThisFunc::TokenType::NUMBER);
  RC_ASSERT(std::stoi(token.lexeme) == num);
}

RC_GTEST_PROP(Scanner, aFloatIsScannedAsNumber, (const double num)){
  std::stringstream stream;
  stream << std::fixed << num;
  ThisFunc::Scanner scanner(&stream);

  ThisFunc::Token token = scanner.scan();

  RC_ASSERT(token.type == ThisFunc::TokenType::NUMBER);
  RC_ASSERT(token.lexeme == stream.str());
}

RC_GTEST_PROP(Scanner, aNumberMayOnlyHaveOneDecimalDot, (const float num)){
  std::stringstream stream;
  stream << std::fixed << num << ".124";

  ThisFunc::Scanner scanner(&stream);
  ThisFunc::Token token = scanner.scan();

  RC_ASSERT(token.type == ThisFunc::TokenType::ERROR);
}

RC_GTEST_PROP(Scanner, charactersAreReadOnDemand, ()){

  char a = *rc::gen::inRange('a','z');
  std::string as;
  as.push_back(a);

  char b = *rc::gen::inRange('a','z');
  std::string bs;
  bs.push_back(b);

  std::stringstream stream;
  stream << a << ' ' << b << ';';

  ThisFunc::Scanner scanner(&stream);
  ThisFunc::Token token1 = scanner.scan();

  RC_ASSERT(token1.lexeme == as);
  RC_ASSERT(stream.peek() == ' ');

  ThisFunc::Token token2 = scanner.scan();

  RC_ASSERT(token2.lexeme == bs);
  RC_ASSERT(stream.peek() == ';');
}

RC_GTEST_PROP(Scanner, onlyAlphaNumerics, ()){

  char a = *rc::gen::inRange(14,31);

  std::stringstream stream;
  stream << a;

  ThisFunc::Scanner scanner(&stream);
  ThisFunc::Token token = scanner.scan();

  std::cout<<token.lexeme<<std::endl;
  RC_ASSERT(token.type == ThisFunc::TokenType::ERROR);
}
