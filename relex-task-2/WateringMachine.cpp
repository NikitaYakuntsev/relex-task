//
// Created by kit on 23.06.15.
//

#include "WateringMachine.h"


bool WateringMachine::isBusy(unsigned long currTime) {
    /*
    bool result = currTime - _startTime <= WORK_TIME;
    if (!result)
        _currentFlowerbed = nullptr;
    */
    return _currentFlowerbed != nullptr;
}

WateringMachine::WateringMachine() : _currentFlowerbed(nullptr) { }

void WateringMachine::moveTo(Flowerbed* flowerbed) {
    _currentFlowerbed = flowerbed; //this takes 5 minutes. Let the gardened move this machine
    //here should be initialization of WORK_TIME in next versions.
}

void WateringMachine::waterCurrentFlowerbed(unsigned long currTime) {
    _startTime = currTime;
    _currentFlowerbed->watering(currTime + WORK_TIME);
    //we are watering. seriously!
    //this action takes WORK_TIME delay.
}

int WateringMachine::getCurrentFlowerbedIndex() const {
    return _currentFlowerbed->getIndex();
}

int WateringMachine::getWorkTime() const {
    return WORK_TIME;
}
