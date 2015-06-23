//
// Created by kit on 23.06.15.
//

#ifndef RELEX_TASK_FLOWERBED_H
#define RELEX_TASK_FLOWERBED_H


#include "Sensor.h"
#include "common.h"

class Flowerbed {
public:
    Flowerbed(unsigned int index);
    void watering(unsigned long currTime);
    bool couldBeWatered(unsigned long currTime);
    int getSensorValue() const; //there would be type selection in the next tasks
    int getTempLimit() const;

private:
    static const int WATERING_DELAY = 4 * 60 * MINUTE;
    unsigned int _index;
    const int TEMP_LIMIT = 30;

    Sensor _tempSensor; //array of sensors
    long _lastWatering;

};


#endif //RELEX_TASK_FLOWERBED_H
