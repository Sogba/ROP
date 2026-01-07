#include "qol.h"

int getCurrentSynchronizationMode(int argc, char* argv[]) {

    if (argc <= 1)
        return syncMethod::ATOMIC;

    char c = *argv[1];

    switch (c) {
        case 'm': return syncMethod::MUTEX;
        case 's': return syncMethod::SEMAPHORE;
        case 'c': return syncMethod::CONDITION;
        case 'a': return syncMethod::ATOMIC;
        case 'n': return syncMethod::NO;
        default:  return syncMethod::ATOMIC;
    }
}
