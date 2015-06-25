//
// Created by kit on 23.06.15.
//

#ifndef RELEX_TASK_WATERINGMACHINE_H
#define RELEX_TASK_WATERINGMACHINE_H

#include "common.h"
#include "Flowerbed.h"

class WateringMachine {
private:
    int _workTime;

    unsigned long _commandTime;
    long _startTime; //working state flag, -1 if not working, used in "alreadyWatering"
    Flowerbed* _currentFlowerbed;

    bool _alreadyMoving; //moving flag

    unsigned int _lastFlowerbedIndex;



public:

    WateringMachine();

    Flowerbed * getCurrentFlowerbed() const;
    int getWorkTime() const;
    unsigned long getCommandTime() const;
    void moveTo(Flowerbed *flowerbed, unsigned long currTime);
    void waterCurrentFlowerbed(unsigned long currTime);
    bool isBusy(unsigned long currTime);

    int getState(unsigned long currTime);
    unsigned int getLastFlowerbedIndex();

    void setNotBusy();

    bool alreadyWatering();
    bool alreadyMoving();
};


#endif //RELEX_TASK_WATERINGMACHINE_H
