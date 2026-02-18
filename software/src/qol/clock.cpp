#include "qol.h"
#include <chrono>
#include <ctime>
#include <format>
#include <string>
#include <thread>
#include <vector>

bool clocksSetted = false;
bool emptyZero = true;


namespace{
  int errorMiliseconds = 300;
  float speedQ;
}

namespace clk {
  void resetClock(clk::clock *clock){
    clock->start = std::chrono::steady_clock::now();
  }

  bool setupClocks(std::vector<clk::clock *> clocks, float speedQInput){
    speedQ = speedQInput;

    for(auto clock : clocks)
      resetClock(clock);
    
    clocksSetted = true;
    return true;
  }

  void clockIncrement(clk::clock *clock){
    if(!clocksSetted)
      return;

    auto now = std::chrono::steady_clock::now();

    if (now - clock->start >= std::chrono::milliseconds(static_cast<int>(1000/ speedQ))) {
        clock->seconds++;
        clock->start += std::chrono::milliseconds(static_cast<int>(1000/ speedQ));
    }

    if(clock->seconds >= 60){
      if(clock->makeErrors)
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(errorMiliseconds/ speedQ)));
      clock->minutes++;
      clock->seconds = 0;
    }

    if(clock->minutes >= 60){
      if(clock->makeErrors)
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(errorMiliseconds/ speedQ)));
      clock->hours++;
      clock->minutes = 0;
    }

    if(clock->hours >= 24){
      if(clock->makeErrors)
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(errorMiliseconds/ speedQ)));
      clock->hours = 0;
    }
  }

  clk::clock zeroClockValues(){
    clk::clock clock;
    clock.hours = 0;
    clock.minutes = 0;
    clock.seconds = 45;
    return clock;
  }

  clk::clock nowClockValues(){
    clk::clock clock;

    time_t timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm mytm;
    localtime_s(&mytm, &timestamp);

    clock.hours = mytm.tm_hour;
    clock.minutes = mytm.tm_min;
    clock.seconds = mytm.tm_sec;
    
    return clock;
  }
}