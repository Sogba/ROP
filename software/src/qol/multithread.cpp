#include "qol.h"
#include <atomic>
#include <chrono>
#include <semaphore>
#include <thread>
#include <mutex>

std::mutex mutex;
std::atomic<clk::clock*> atomicClock;
std::counting_semaphore<1> semaphore(1);

void atomicSync(clk::clock* clock){
  static clk::clock local;

  local = *clock;

  clk::clockIncrement(&local);
  *clock = local;
  atomicClock.store(&local, std::memory_order_release);
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
      case syncMethod::ATOMIC: atomicSync(clock); break;
      case syncMethod::MUTEX: mutexSync(clock); break;
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
    case syncMethod::MUTEX: mutexResolve(clock, renderClock); return true;
    case syncMethod::SEMAPHORE: semaphoreResolve(clock, renderClock); return true;
    case syncMethod::NO: *renderClock = *clock; return true;
  }
  return false;
}