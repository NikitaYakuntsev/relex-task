//
// Created by kit on 23.06.15.
//

#include "WateringMachine.h"


bool WateringMachine::isBusy(unsigned long currTime) {
    /*
    bool result = currTime - _startTime <= workTime;
    if (!result)
        _currentFlowerbed = nullptr;
    */
    return _currentFlowerbed != nullptr;
}

WateringMachine::WateringMachine() : _currentFlowerbed(nullptr) { }

void WateringMachine::moveTo(Flowerbed* flowerbed) {
    _currentFlowerbed = flowerbed;
    if (flowerbed != nullptr)
        _workTime = flowerbed->getTimeToWater();
}

void WateringMachine::waterCurrentFlowerbed(unsigned long currTime) {
    _startTime = currTime;
    _currentFlowerbed->watering(currTime + _workTime);
    //we are watering. seriously!
    //this action takes WORK_TIME delay.
}

Flowerbed * WateringMachine::getCurrentFlowerbed() const {
    return _currentFlowerbed;
}

int WateringMachine::getWorkTime() const {
    return _workTime;
}
