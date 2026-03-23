#include <iostream>
#include "core.h"

namespace message {
  void start(){ std::cout << "ROP started\n"; }
  void end(){ std::cout << "ROP ended\n"; }
}