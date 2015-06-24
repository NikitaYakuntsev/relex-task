//
// Created by kit on 23.06.15.
//

#ifndef RELEX_TASK_GARDENER_H
#define RELEX_TASK_GARDENER_H


#include "Flowerbed.h"
#include "WateringMachine.h"
#include <iostream>
#include <fstream>
#include <thread>

class Gardener {
public:
    Gardener();
    void startWork(); //infinite loop with time increment here
    void moveMachine(int machineIndex, int flowerbedIndex); //sleep 5 minutes
    void doWatering(int machineIndex); //sleep 10 minutes
    void loadDataFromFile();
private:
    unsigned long _time;
    //Flowerbed _flowerbed; //there would be an array in the next versions
    std::vector<Flowerbed> _flowerbeds;
    WateringMachine _machine; //array in the next versions
    std::string secondsToHoursAndMins(unsigned long seconds);

};


#endif //RELEX_TASK_GARDENER_H
