#include "qol.h"
#include <atomic>
#include <chrono>
#include <semaphore>
#include <thread>
#include <mutex>

std::mutex mutex;
std::atomic<clk::clock*> atomicClock;
std::counting_semaphore<1> semaphore(1);

void atomicSync(){
  static clk::clock local;

  clk::clockIncrement(&local);
  atomicClock.store(&local, std::memory_order_release);
}

void conditionSync(clk::clock *clock){

}

void mutexSync(clk::clock *clock){
  mutex.lock();
  clk::clockIncrement(clock);
  mutex.unlock();
}

void semaphoreSync(clk::clock *clock){
  semaphore.acquire();
  clk::clockIncrement(clock);
  semaphore.release();
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

    std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_SLEEP));
  }
}

void atomicResolve(clk::clock *renderClock){
  *renderClock = *atomicClock.load(std::memory_order_acquire);
}

void conditionResolve(clk::clock *clock, clk::clock *renderClock){

}

void mutexResolve(clk::clock *clock, clk::clock *renderClock){
  if(!mutex.try_lock())
    return;
  *renderClock = *clock;
  mutex.unlock();
}

void semaphoreResolve(clk::clock *clock, clk::clock *renderClock){
  if(!semaphore.try_acquire())
    return;

  *renderClock = *clock;

  semaphore.release();
}

bool resolveSync(clk::clock *clock, int syncMode, clk::clock *renderClock){
  switch (syncMode) {
    case syncMethod::ATOMIC: atomicResolve(renderClock); return true;
    case syncMethod::CONDITION: conditionResolve(clock, renderClock); return true;
    case syncMethod::MUTEX: mutexResolve(clock, renderClock); return true;
    case syncMethod::SEMAPHORE: semaphoreResolve(clock, renderClock); return true;
    case syncMethod::NO: return true;
  }
  return false;
}