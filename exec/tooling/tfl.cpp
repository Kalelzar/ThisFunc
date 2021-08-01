#include <ThisFunc/Parser.hpp>
#include <fstream>
#include <string>

int main (i32 argv, char** argc) {
  if (argv == 1) {
    std::cout << "ThisFunc-Lisp Transpiler.\n"
                 "ThisFunc THIS_FUNC_VERSION\n"
                 "usage: tfl <filename> [output_filename]\n";
  } else {
    try {
      std::ifstream          file (argc[1]);
      ThisFunc::Parser       parser (&file);
      ThisFunc::AST::BodyPtr result = parser.parse ( );

      if (parser.hadError) {
        std::cerr << "Failed to parse '" << argc[1] << "'" << std::endl;
        return 1;
      }

      auto opt = result->optimal ( );
      if (argv == 2) {
        opt->print ( );
      } else {
        std::ofstream outfile (argc[2]);
        opt->print (&outfile);
      }
    } catch (std::runtime_error& e) {
      std::cerr << "Runtime Error: " << e.what ( ) << std::endl;
      return 3;
    }
  }
  return 0;
}
