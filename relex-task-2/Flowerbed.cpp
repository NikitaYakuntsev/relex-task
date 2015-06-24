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
