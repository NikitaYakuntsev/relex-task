//
// Created by kit on 23.06.15.
//

#include "WateringMachine.h"


bool WateringMachine::isBusy(unsigned long currTime) {

    bool result = (_currentFlowerbed != nullptr);
    //probably result = !_alreadyMoving && _startTime == -1; but _currentFlowerbed will stay for last position

    //return _currentFlowerbed != nullptr;
    return result;
}

WateringMachine::WateringMachine() : _currentFlowerbed(nullptr),
                                     _startTime(-1),
                                     _alreadyMoving(false),
                                     _lastFlowerbedIndex(0) { }


void WateringMachine::moveTo(Flowerbed *flowerbed, unsigned long currTime) {
    _alreadyMoving = true;
    if (flowerbed != nullptr) {
        _currentFlowerbed = flowerbed;
        //_lastFlowerbedIndex = flowerbed->getIndex();
        //_workTime = flowerbed->getTimeToWater() + flowerbed->getTimeToMove(); //to get to flowerbed - never used
        _commandTime = currTime;
    }


}

void WateringMachine::waterCurrentFlowerbed(unsigned long currTime) {
    _alreadyMoving = false;
    if (_startTime == -1) {
        _startTime = currTime;
        _currentFlowerbed->watering(currTime + _currentFlowerbed->getTimeToWater()); //set the end time of watering process
    }

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
// 3 - could be free
//      0          1        2       3
//  |---------|----------|--------|---
//  ^         ^          ^        ^
//command;waterStart;waterEnd;AtStartPos
//
//in the task 5 it could be free after waterEnd point.
int WateringMachine::getState(unsigned long currTime) {
    int state = 3;
    if (isBusy(currTime)) {
        unsigned long waterStart = _commandTime + _currentFlowerbed->getTimeToMove(_lastFlowerbedIndex);
        if ((_commandTime <= currTime) && (currTime < waterStart))
            state = 0;

        unsigned long waterEnd = waterStart + _currentFlowerbed->getTimeToWater();
        if ((waterStart <= currTime) && (currTime < waterEnd)) {
            state = 1;
            _alreadyMoving = false;
        }

        //there is no period when wateringmachine is returning back to start position
        /*
        if ((waterEnd <= currTime) && (currTime < waterEnd + _currentFlowerbed->getTimeToMove()))
            state = 2;
        */
        if (currTime >= waterEnd) {  // + _currentFlowerbed->getTimeToMove()) {
            state = 3;

            _alreadyMoving = false;

        }
    }

    return state;
}

void WateringMachine::setNotBusy() {
    if (_currentFlowerbed != nullptr) {
        _startTime = -1;
        _alreadyMoving = false;
        _lastFlowerbedIndex = _currentFlowerbed->getIndex();
        _currentFlowerbed = nullptr; //probably commented line
    }
}

unsigned long WateringMachine::getCommandTime() const {
    return _commandTime;
}


bool WateringMachine::alreadyWatering() {
    return _startTime != -1;
}

bool WateringMachine::alreadyMoving() {
    return _alreadyMoving;
}

unsigned int WateringMachine::getLastFlowerbedIndex() {
    return _lastFlowerbedIndex;
}
