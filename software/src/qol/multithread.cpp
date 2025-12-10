#include "qol.h"

void threadIncrementingClock(clk::clock *clock, bool *threadControl){
  while(*threadControl)
    clk::clockIncrement(clock);
}