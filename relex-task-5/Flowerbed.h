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
    void setIndex(int index);

    const std::map<SensorType, Sensor> & getSensors() const;
    void setSensors(const std::map<SensorType, Sensor> &sensors);
    void setValueLimits(const std::map<SensorType, int> &valueLimits);
    void setDistances(const std::vector<int> &distances);

    int getTimeToMove() const;
    void setTimeToMove(int timeToMove);
    int getTimeToWater() const;
    void setTimeToWater(int timeToWater);



private:
    const int WATERING_DELAY = 4 * 60 * MINUTE;
    unsigned int _index;

    std::map<SensorType, int> _valueLimits; //limits for sensor type
    std::map<SensorType, Sensor> _sensors;

    std::vector<int> _distances; //array where Ai shows how much time needs to get from this flowerbed to Ith

    long _lastWatering;



private:
    int _timeToMove;
    int _timeToWater;




};


#endif //RELEX_TASK_FLOWERBED_H
