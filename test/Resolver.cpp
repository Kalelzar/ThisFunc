#include <ThisFunc/Parser.hpp>
#include <ThisFunc/Resolver.hpp>
#include <ThisFunc/TypeDeduction.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <rapidcheck/Assertions.h>
#include <rapidcheck/gtest.h>

namespace ThisFunc::AST {


TEST (Resolver, ConstantFunction) {
  Resolver          r;
  std::stringstream inout;
  inout << "const <- 5";
  ThisFunc::Parser parser (&inout);
  BodyPtr          body = parser.parse ( );
  ASSERT_FALSE (parser.hadError);
  r.resolve (body);
  auto f = r.get ("const");
  //  ASSERT_TRUE (f->name == "const");
}

}     // namespace ThisFunc::AST
