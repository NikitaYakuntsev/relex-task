//
// Created by kit on 23.06.15.
//

#include "Flowerbed.h"

Flowerbed::Flowerbed(unsigned int index)
        : _index(index), _tempSensor(Sensor(SensorType::temperature)) { }
