//
// Created by kit on 23.06.15.
//


#include "Sensor.h"
Sensor::Sensor(const SensorType& type) : _type(type) { }


const SensorType & Sensor::getType() const {
    return _type;
}

int Sensor::getValue() const {
    return _value;
}

void Sensor::generateValue(unsigned long currTime) {
    //_value = rand() % 50 + 10;
    if (_schedule.find(currTime) != std::end(_schedule))
        _value = _schedule.at(currTime);
    else {
        ///TODO find previous time
    }
}

Sensor::Sensor(const SensorType &type, const std::map<long, int> &schedule) : _type(type), _schedule(schedule) { }

Sensor::Sensor() {
    _type = temperature;
}
