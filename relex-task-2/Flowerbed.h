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
    Flowerbed();
    void watering(unsigned long currTime);
    bool couldBeWatered(unsigned long currTime);
    int getSensorValue(const SensorType &sensorType, const long currTime); //there would be type selection in the next tasks
    int getSensorLimit(const SensorType &sensorType) const;
    int getIndex() const;

    void setSensors(const std::map<SensorType, Sensor> &sensors);

    void setValueLimits(const std::map<SensorType, int> &valueLimits);

private:
    const int WATERING_DELAY = 4 * 60 * MINUTE;
    unsigned int _index;
    const int TEMP_LIMIT = 30; //would be array of pair <type, limit>

    std::map<SensorType, int> _valueLimits; //limits for sensor type
    std::map<SensorType, Sensor> _sensors;
    //Sensor _tempSensor; //array of sensors
    long _lastWatering;



};


#endif //RELEX_TASK_FLOWERBED_H
