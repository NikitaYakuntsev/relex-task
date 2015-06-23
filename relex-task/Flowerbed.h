//
// Created by kit on 23.06.15.
//

#ifndef RELEX_TASK_FLOWERBED_H
#define RELEX_TASK_FLOWERBED_H


#include "Sensor.h"
#include "common.h"
#include <string>
#include <sstream>

class Flowerbed {
public:

    Flowerbed(unsigned int index);
    void watering(unsigned long currTime);
    bool couldBeWatered(unsigned long currTime);
    int getSensorValue(); //there would be type selection in the next tasks
    int getTempLimit() const;

private:
    const int WATERING_DELAY = 4 * 60 * MINUTE;
    unsigned int _index;
    const int TEMP_LIMIT = 30; //would be array of pair <type, limit>

    Sensor _tempSensor; //array of sensors
    long _lastWatering;



};


#endif //RELEX_TASK_FLOWERBED_H
