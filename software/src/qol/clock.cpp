#include <chrono>
#include <ctime>
#include <format>
#include <string>
#include <thread>
#include <vector>

bool clocksSetted = false;
bool emptyZero = true;

namespace clk {
    struct clock {
    short int seconds = 0;
    short int minutes = 0;
    short int hours = 0;
    std::chrono::time_point<std::chrono::steady_clock> start;
    bool makeErrors = false;
  };

  void resetClock(clk::clock *clock){
    clock->start = std::chrono::steady_clock::now();
  }

  bool setupClocks(std::vector<clk::clock *> clocks){
    if(clocksSetted)
      return false;

    for(auto clock : clocks)
      resetClock(clock);
    
    clocksSetted = true;
    return true;
  }

  void clockIncrement(clk::clock *clock){
    if(!clocksSetted)
      return;
    if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - clock->start) >= std::chrono::milliseconds(999)){
      clock->seconds++;
      resetClock(clock);
    }
    if(clock->seconds >= 60){
      if(clock->makeErrors)
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
      clock->minutes++;
      clock->seconds = 0;
    }
    if(clock->minutes >= 60){
      clock->hours++;
      clock->minutes = 0;
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

  std::string clockToString(clk::clock *clock){
    if(emptyZero)
      return std::format("{:02}:{:02}:{:02}", clock->hours, clock->minutes, clock->seconds);

    return std::format("{}:{}:{}", clock->hours, clock->minutes, clock->seconds);
  }
}