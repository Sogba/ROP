#include "qol.h"

int getCurrentSynchronizationMode(int argc, char* argv[]) {

    if (argc <= 1)
        return synchronizationMethod::ATOMIC;

    char c = *argv[1];

    switch (c) {
        case 'm': return synchronizationMethod::MUTEX;
        case 's': return synchronizationMethod::SEMAPHORE;
        case 'c': return synchronizationMethod::CONDITION;
        case 'a': return synchronizationMethod::ATOMIC;
        case 'l': return synchronizationMethod::LOCK;
        default:  return synchronizationMethod::ATOMIC;
    }
}
