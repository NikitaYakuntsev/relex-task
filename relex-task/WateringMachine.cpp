//
// Created by kit on 23.06.15.
//

#include "WateringMachine.h"

bool WateringMachine::isBusy(unsigned long currTime) {
    return (currTime - startTime) > WORK_TIME ? false : true;
}
