//
// Created by kit on 23.06.15.
//


#include "Sensor.h"
Sensor::Sensor(const SensorType& type) : _type(type) { }


const SensorType &Sensor::getType() const {
    return _type;
}

int Sensor::getValue() const {
    return _value;
}

void Sensor::generateValue() {
    _value = rand() % 50 + 10;
}
