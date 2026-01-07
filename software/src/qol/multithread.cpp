#include "qol.h"
#include <chrono>
#include <thread>

void threadIncrementingClock(clk::clock *clock, bool *threadControl){
  while(*threadControl){
    clk::clockIncrement(clock);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
}