#pragma once

#include <chrono>
#include <cstddef>

//terminalOutput.cpp
namespace message{
  void start();
  void end();
};

//clock.cpp
namespace clk {
    struct clock {
    short int seconds;
    short int minutes;
    short int hours;
    std::chrono::time_point<std::chrono::steady_clock> start;
    bool makeErrors = false;
  };


  bool setupClocks(std::vector<clk::clock *> clocks);
  void clockIncrement(clk::clock *clock);
  clk::clock nowClockValues();
  clk::clock zeroClockValues();
  std::string clockToString(clk::clock *clock);
}

//multithread.cpp
void threadIncrementingClock(clk::clock *clock, bool *threadControl);