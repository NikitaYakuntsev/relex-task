//
// Created by kit on 23.06.15.
//

#include "WateringMachine.h"


bool WateringMachine::isBusy(unsigned long currTime) {

    bool result = (currTime - _startTime <= _workTime ) || (_currentFlowerbed != nullptr);

    //return _currentFlowerbed != nullptr;
    return result;
}

WateringMachine::WateringMachine() : _currentFlowerbed(nullptr) { }

void WateringMachine::moveTo(Flowerbed* flowerbed) {
    _currentFlowerbed = flowerbed;
    if (flowerbed != nullptr)
        _workTime = flowerbed->getTimeToWater() + 2*flowerbed->getTimeToMove(); //to get to flowerbed and return back
}

void WateringMachine::waterCurrentFlowerbed(unsigned long currTime) {
    _startTime = currTime;
    _currentFlowerbed->watering(currTime + _workTime - 2*_currentFlowerbed->getTimeToMove()); //set the end time of watering process
}

Flowerbed * WateringMachine::getCurrentFlowerbed() const {
    return _currentFlowerbed;
}

int WateringMachine::getWorkTime() const {
    return _workTime;
}


// 0 - moving to
// 1 - start watering
// 2 - moving back
int WateringMachine::getState(unsigned long currTime) {
    
}
