//
// Created by kit on 23.06.15.
//

#ifndef RELEX_TASK_SENSOR_H
#define RELEX_TASK_SENSOR_H

#include <stdlib.h>
#include "common.h"

enum SensorType {
    temperature,
    humidity
};

class Sensor {
public:
    Sensor();
    Sensor(const SensorType &type);
    Sensor(const SensorType &type, const std::map<long, int> &schedule);

    const SensorType & getType() const;

    int getValue() const;

    void generateValue(unsigned long currTime);


private:
    SensorType _type;
    int _value;
    std::map<long, int> _schedule;
    //for next version there should be array of pair <time, value>
};


#endif //RELEX_TASK_SENSOR_H
