//
// Created by kit on 23.06.15.
//

#include "Flowerbed.h"


Flowerbed::Flowerbed(unsigned int index)
        : _index(index), _tempSensor(Sensor(SensorType::temperature)), _lastWatering(-1 * WATERING_DELAY - MINUTE) { }

void Flowerbed::watering(unsigned long currTime) {
        _lastWatering = currTime;
}


bool Flowerbed::couldBeWatered(unsigned long currTime) {
        return currTime - _lastWatering >= WATERING_DELAY;
}

int Flowerbed::getSensorValue() {
        _tempSensor.generateValue();
        return _tempSensor.getValue();
}

int Flowerbed::getTempLimit() const {
        return TEMP_LIMIT;
}


int Flowerbed::getIndex() const {
        return _index;
}
