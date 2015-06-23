//
// Created by kit on 23.06.15.
//

#ifndef RELEX_TASK_FLOWERBED_H
#define RELEX_TASK_FLOWERBED_H


#include "Sensor.h"

class Flowerbed {
public:

    Flowerbed(unsigned int index);

private:
    unsigned int _index;
    const int TEMP_LIMIT = 30;
    Sensor _tempSensor;

};


#endif //RELEX_TASK_FLOWERBED_H
