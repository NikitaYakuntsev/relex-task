//
// Created by kit on 23.06.15.
//

#include "Flowerbed.h"


Flowerbed::Flowerbed(unsigned int index)
        : _index(index), /*_tempSensor(Sensor(SensorType::temperature)),*/ _lastWatering(-1 * WATERING_DELAY - MINUTE) { }

void Flowerbed::watering(unsigned long currTime) {
        _lastWatering = currTime;
}


bool Flowerbed::couldBeWatered(unsigned long currTime) {
        return currTime - _lastWatering >= WATERING_DELAY;
}

int Flowerbed::getSensorValue(const SensorType &sensorType, const long currTime) {
        _sensors[sensorType].generateValue(currTime);
        return _sensors[sensorType].getValue();
}

int Flowerbed::getSensorLimit(const SensorType &sensorType) const {
        return _valueLimits.at(sensorType);
}


int Flowerbed::getIndex() const {
        return _index;
}

Flowerbed::Flowerbed() {
    _index = 0;
}

void Flowerbed::setSensors(const std::map<SensorType, Sensor> &sensors) {
    _sensors = sensors;
}

void Flowerbed::setValueLimits(const std::map<SensorType, int> &valueLimits) {
    _valueLimits = valueLimits;
}

const std::map<SensorType, Sensor> & Flowerbed::getSensors() const {
    return _sensors;
}

void Flowerbed::setIndex(int index) {
    _index = index;
    _lastWatering = -1 * WATERING_DELAY - MINUTE;
}

int Flowerbed::getTimeToMove() const {
    return _timeToMove;
}

void Flowerbed::setTimeToMove(int timeToMove) {
    _timeToMove = timeToMove;
}

int Flowerbed::getTimeToWater() const {
    return _timeToWater;
}

void Flowerbed::setTimeToWater(int timeToWater) {
    _timeToWater = timeToWater;
}

void Flowerbed::setDistances(const std::vector<int> &distances) {
    _distances = distances;
}
