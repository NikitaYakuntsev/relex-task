//
// Created by kit on 23.06.15.
//

#ifndef RELEX_TASK_SENSOR_H
#define RELEX_TASK_SENSOR_H

#include <stdlib.h>

enum SensorType {
    temperature,
    humidity
};

class Sensor {
public:
    Sensor(const SensorType &type);

    const SensorType &getType() const;

    int getValue() const;

    void generateValue();

private:
    SensorType _type;
    int _value;
    //for next version there should be array of pair <time, value>
};


#endif //RELEX_TASK_SENSOR_H
