//
// Created by kit on 23.06.15.
//

#ifndef RELEX_TASK_WATERINGMACHINE_H
#define RELEX_TASK_WATERINGMACHINE_H

#include "common.h"
#include "Flowerbed.h"

class WateringMachine {
private:
    unsigned int _workTime;
    unsigned long _commandTime;
    unsigned long _startTime;
    Flowerbed* _currentFlowerbed;



public:

    WateringMachine();

    Flowerbed * getCurrentFlowerbed() const;
    int getWorkTime() const;
    void moveTo(Flowerbed* flowerbed);
    void waterCurrentFlowerbed(unsigned long currTime);
    bool isBusy(unsigned long currTime);

    int getState(unsigned long currTime);
};


#endif //RELEX_TASK_WATERINGMACHINE_H
