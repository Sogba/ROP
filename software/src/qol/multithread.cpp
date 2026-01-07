#include "qol.h"
#include <chrono>
#include <thread>
#include <mutex>

std::mutex myMutex;

void conditionSync(clk::clock *clock){
  
}

void mutexSync(clk::clock *clock){
  myMutex.lock();
  clk::clockIncrement(clock);
  myMutex.unlock();
}

void semaphoreSync(clk::clock *clock){

}

void threadIncrementingClock(clk::clock *clock, bool *threadControl, int syncMode){
  while(*threadControl){

    switch (syncMode) {
      case syncMethod::ATOMIC: break;
      case syncMethod::CONDITION: conditionSync(clock); break;
      case syncMethod::MUTEX: mutexSync(clock) ;
      case syncMethod::SEMAPHORE: semaphoreSync(clock); break;
      case syncMethod::NO:
        clk::clockIncrement(clock);
        break;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
}

void conditionResolve(clk::clock *clock, clk::clock *renderClock){

}

void mutexResolve(clk::clock *clock, clk::clock *renderClock){
  if(!myMutex.try_lock())
    return;
  *renderClock = *clock;
  myMutex.unlock();
}

void semaphoreResolve(clk::clock *clock, clk::clock *renderClock){

}

bool resolveSync(clk::clock *clock, int syncMode, clk::clock *renderClock){
  switch (syncMode) {
    case syncMethod::ATOMIC: return true;
    case syncMethod::CONDITION: conditionResolve(clock, renderClock); return true;
    case syncMethod::MUTEX: mutexResolve(clock, renderClock); return true;
    case syncMethod::SEMAPHORE: semaphoreResolve(clock, renderClock); return true;
    case syncMethod::NO: return true;
  }
  return false;
}