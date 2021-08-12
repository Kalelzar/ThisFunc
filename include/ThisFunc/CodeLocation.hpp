#ifndef CODELOCATION_H
#define CODELOCATION_H

#include <Kal/defs.hpp>

namespace ThisFunc::VM {

struct CodeLocation {
  u32 line;
  u32 column;
};

}     // namespace ThisFunc::VM


#endif /* CODELOCATION_H */
