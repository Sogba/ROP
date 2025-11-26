#include <iostream>
#include "terminalOutput.h"

void message::start() {
  std::cout << "ROP started\n";
}

void message::end(){
  std::cout << "ROP ended\n";
}