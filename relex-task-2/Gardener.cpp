//
// Created by kit on 23.06.15.
//

#include "Gardener.h"

void Gardener::moveMachine(int flowerbedIndex = 0, int machineIndex = 0) {
    //returning to start position
    if (flowerbedIndex == -1) {
        std::cout << "_______________" << std::endl;
        std::cout << "Gardener is moving machine " << machineIndex << " to start position" <<
        ". Time since start: " << secondsToHoursAndMins(_time) << "." << std::endl;
        _machine.moveTo(nullptr); //here should be selection by index
        _time += 5 * MINUTE;
        std::cout << "Machine " << machineIndex << " moved to start position" <<
        ". Time since start: " << secondsToHoursAndMins(_time) << "." << std::endl;
        std::cout << "_______________" << std::endl;
    } else {
        std::cout << "_______________" << std::endl;
        std::cout << "Gardener is moving machine " << machineIndex << " to flowerbed " << flowerbedIndex <<
        ". Time since start: " << secondsToHoursAndMins(_time) << "." << std::endl;
        _machine.moveTo(&_flowerbeds[flowerbedIndex]); //here should be selection by index
        _time += 5 * MINUTE;
        std::cout << "Machine " << machineIndex << " moved to flowerbed " << flowerbedIndex <<
        ". Time since start: " << secondsToHoursAndMins(_time) << "." << std::endl;
        std::cout << "_______________" << std::endl;
    }
}

void Gardener::doWatering(int machineIndex = 0) {
    std::cout << "_______________" << std::endl;
    std::cout << "Machine " << machineIndex << " is watering flowerbed " << _machine.getCurrentFlowerbedIndex() <<
            ". Time since start: " << secondsToHoursAndMins(_time) << "." << std::endl;
    _machine.waterCurrentFlowerbed(_time);
    _time += _machine.getWorkTime();
    //_flowerbed.watering(_time);
    std::cout << "Machine " << machineIndex << " watered flowerbed " << _machine.getCurrentFlowerbedIndex() <<
            ". Time since start: " << secondsToHoursAndMins(_time) << "." << std::endl;
    std::cout << "_______________" << std::endl;

}

Gardener::Gardener()  { }


// There should be a correct compare expression, based on sensor type.
bool Gardener::needToBeWatered(Flowerbed &f) {
    bool result = false;
    ///TODO
    for (auto &sens : f.getSensors())
        result |= (f.getSensorValue(sens.first, _time) > f.getSensorLimit(sens.first));
    return result;

}


void Gardener::startWork() {
    loadDataFromFile();
    _time = 0;
    while (true) {

        for (int i = 0; i < _flowerbeds.size(); i++) {
            Flowerbed _flowerbed = _flowerbeds[i];
            if (_flowerbed.couldBeWatered(_time))
                if (needToBeWatered(_flowerbed))
                    if (!_machine.isBusy(_time)) {
                        moveMachine(i);
                        doWatering();
                        moveMachine(-1);
            }
        }
        _time += 5 * MINUTE;
        std::this_thread::sleep_for(std::chrono::seconds(1));

    }


}

std::string Gardener::secondsToHoursAndMins(unsigned long seconds) {
    int minutes = seconds / 60;
    int hours = minutes / 60;
    std::stringstream strm;

    strm <<  int(hours) << " hours; " << int(minutes % 60)
        << " minutes; " << int(seconds % 60) << " seconds";
    std::string result = strm.str();
    return result;
}

void Gardener::loadDataFromFile() {

    //file beds.txt has number n in the first line,
    //then n lines with m_i - number of sensors, connected to this flowerbed
    //then m_i pairs of numbers p_j l_j, where p_j is type of sensor (0 - temp, 1 - humidity)
    //and l_j is limit for this type
    //file i-p_j.txt contains number (size) and then (size) pairs <time, value> for p_j sensor and i flowerbed
    std::ifstream bin("beds.txt");
    int n;
    bin >> n;
    _flowerbeds.resize(n);
    //flowerbeds loop
    for (int i = 0; i < n; i++) {
        int m;
        bin >> m;
        std::map<SensorType, Sensor> sensors;
        std::map<SensorType, int> valueLimits;
        //sensors loop
        for (int j = 0; j < m; j++) {
            int sensType, sensLimit;
            bin >> sensType >> sensLimit;

            std::stringstream sstream;
            sstream << i << "-" << j << ".txt";
            std::string name = sstream.str();
            std::ifstream sin(name.c_str());

            int size;
            sin >> size; //number of pairs <time, value> for sensor
            std::map<long, int> schedule;
            for (int k = 0; k < size; k++) {
                long time;
                int value;
                sin >> time >> value;
                schedule[time] = value;
            }
            sin.close();

            SensorType type;
            switch (sensType) {
                case 0:
                    type = temperature;
                    break;
                case 1:
                    type = humidity;
                    break;
            }

            Sensor sen(type, schedule);
            sensors[type] = sen;
            valueLimits[type] = sensLimit;
        }
        _flowerbeds[i].setIndex(i);
        _flowerbeds[i].setSensors(sensors);
        _flowerbeds[i].setValueLimits(valueLimits);
    }
    bin.close();
}
