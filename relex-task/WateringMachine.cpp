//
// Created by kit on 23.06.15.
//

#include "WateringMachine.h"

bool WateringMachine::isBusy(unsigned long currTime) {
    bool result = currTime - _startTime <= WORK_TIME;
    if (!result)
        _currentFlowerbedIndex = -1;
    return result;
}

WateringMachine::WateringMachine() : _startTime(-1 * WORK_TIME - MINUTE), _currentFlowerbedIndex(-1) { }

void WateringMachine::moveTo(unsigned int flowerbedIndex) {
    _currentFlowerbedIndex = flowerbedIndex; //this takes 5 minutes. Let the gardened move this machine
}

void WateringMachine::waterCurrentFlowerbed(unsigned long currTime) {
    _startTime = currTime;
    //we are watering. seriously!
    //this action takes WORK_TIME delay.
}

int WateringMachine::getCurrentFlowerbedIndex() const {
    return _currentFlowerbedIndex;
}

int WateringMachine::getWorkTime() const {
    return WORK_TIME;
}
