//
// Created by kit on 23.06.15.
//

#ifndef RELEX_TASK_GARDENER_H
#define RELEX_TASK_GARDENER_H


#include "Flowerbed.h"
#include "WateringMachine.h"

class Gardener {
public:
    void startWork(); //infinite loop with time increment here
    void moveMachine(int machineIndex, int flowerbedIndex); //sleep 5 minutes
    void doWatering(int machineIndex); //sleep 10 minutes
private:
    unsigned long time;
    Flowerbed flowerbed; //there would be an array in the next versions
    WateringMachine machine; //array in the next versions
};


#endif //RELEX_TASK_GARDENER_H
