//
// Created by kit on 23.06.15.
//

#ifndef RELEX_TASK_WATERINGMACHINE_H
#define RELEX_TASK_WATERINGMACHINE_H

#include "common.h"
#include "Flowerbed.h"

class WateringMachine {
private:
    const unsigned int WORK_TIME = 10 * MINUTE;
    unsigned long _startTime;
    Flowerbed* _currentFlowerbed;

public:

    WateringMachine();

    int getCurrentFlowerbedIndex() const;
    int getWorkTime() const;
    void moveTo(Flowerbed* flowerbed);
    void waterCurrentFlowerbed(unsigned long currTime);
    bool isBusy(unsigned long currTime);
};


#endif //RELEX_TASK_WATERINGMACHINE_H
