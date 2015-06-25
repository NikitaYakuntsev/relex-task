//
// Created by kit on 23.06.15.
//

#include "Gardener.h"

void Gardener::moveMachine(int flowerbedIndex = 0, int machineIndex = 0) {
    //returning to start position
    std::cout << "_______________" << std::endl;
    if (flowerbedIndex == -1) {

        std::cout << "Machine " << machineIndex << " is moving to start position" <<
        ". Time since start: " << secondsToHoursAndMins(_time) << "." << std::endl;
        long tmptime = _machines[machineIndex].getCurrentFlowerbed()->getTimeToMove();
        _machines[machineIndex].moveTo(nullptr);

        std::cout << "Machine " << machineIndex << " will be in the start position" <<
        " at time since start: " << secondsToHoursAndMins(_time + tmptime) << "." << std::endl;
    } else {
        std::cout << "Machine " << machineIndex << " is moving to flowerbed " << flowerbedIndex <<
        ". Time since start: " << secondsToHoursAndMins(_time) << "." << std::endl;
        //_time += _flowerbeds[flowerbedIndex].getTimeToMove(); //gardener images time to get the flowerbed
        _machines[machineIndex].moveTo(&_flowerbeds[flowerbedIndex]);

        std::cout << "Machine " << machineIndex << " will be near the flowerbed " << flowerbedIndex <<
        ". Time since start: " << secondsToHoursAndMins(_time + _flowerbeds[flowerbedIndex].getTimeToMove()) << "." << std::endl;
    }
    std::cout << "_______________" << std::endl;
}

void Gardener::doWatering(int machineIndex = 0) {
    std::cout << "_______________" << std::endl;
    std::cout << "Machine " << machineIndex << " will be watering flowerbed " << _machines[machineIndex].getCurrentFlowerbed()->getIndex() <<
    " at time since start: " << secondsToHoursAndMins(_time + _machines[machineIndex].getCurrentFlowerbed()->getTimeToMove()) << "." << std::endl;
    _machines[machineIndex].waterCurrentFlowerbed(_time);
    //_time += _machines[machineIndex].getWorkTime();

    std::cout << "Machine " << machineIndex << " will water flowerbed " << _machines[machineIndex].getCurrentFlowerbed()->getIndex() <<
    " at time since start: " << secondsToHoursAndMins(_time + _machines[machineIndex].getCurrentFlowerbed()->getTimeToWater()) << "." << std::endl;
    std::cout << "_______________" << std::endl;

}

Gardener::Gardener()  { }


// There should be a correct compare expression, based on sensor type.
bool Gardener::needToBeWatered(Flowerbed &f) {
    bool result = false;
    ///TODO check sign!
    for (auto &sens : f.getSensors())
        result |= (f.getSensorValue(sens.first, _time) > f.getSensorLimit(sens.first));
    return result;

}

void Gardener::checkMachines() {
    for (int i = 0; i < _machines.size(); i++) {
        if (!_machines[i].isBusy(_time) && _machines[i].getCurrentFlowerbed() != nullptr)
            moveMachine(-1, i);
    }
}

void Gardener::startWork() {
    loadDataFromFile();
    _time = 0;
    while (true) {
        std::cout << "Time since start: " << secondsToHoursAndMins(_time) << "." << std::endl;
        for (int i = 0; i < _flowerbeds.size(); i++) {
            Flowerbed _flowerbed = _flowerbeds[i];
            if (_flowerbed.couldBeWatered(_time))
                if (needToBeWatered(_flowerbed)) {
                    //find non-busy machine there
                    bool found = false;
                    for (int j = 0; j < _machines.size() && !found; j++)
                        if (!_machines[j].isBusy(_time)) {
                            found = true;
                            moveMachine(i, j);
                            doWatering(j);
                            //moveMachine(-1);
                        }
                }
        }
        checkMachines(); //here you should moveMachine(-1, j) if it's already done, current!=null and !isBusy
        _time += MINUTE;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));


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
    //file machines.txt has number K - number of machines
    //file beds.txt has number N-number of flowerbeds in the first line,
    //then n lines with TM & TW - time to move and time to water
    //then m_i - number of sensors, connected to this flowerbed
    //then m_i pairs of numbers p_j l_j, where p_j is type of sensor (0 - temp, 1 - humidity)
    //and l_j is limit for this type
    //file i-p_j.txt contains number (size) and then (size) pairs <time, value> for p_j sensor and i flowerbed
    std::ifstream min("machines.txt");
    int k;
    min >> k;
    min.close();
    _machines.resize(k);

    std::ifstream bin("beds.txt");
    int n;
    bin >> n;
    _flowerbeds.resize(n);
    //flowerbeds loop
    for (int i = 0; i < n; i++) {

        int timeToMove, timeToWater; //for flowerbed.
        bin >> timeToMove >> timeToWater;
        _flowerbeds[i].setTimeToMove(timeToMove * MINUTE);
        _flowerbeds[i].setTimeToWater(timeToWater * MINUTE);

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


