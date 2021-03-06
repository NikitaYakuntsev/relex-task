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
        _time += 5 * MINUTE;
        _machine.moveTo(nullptr); //here should be selection by index

        std::cout << "Machine " << machineIndex << " moved to start position" <<
        ". Time since start: " << secondsToHoursAndMins(_time) << "." << std::endl;
        std::cout << "_______________" << std::endl;
    } else {
        std::cout << "_______________" << std::endl;
        std::cout << "Gardener is moving machine " << machineIndex << " to flowerbed " << flowerbedIndex <<
        ". Time since start: " << secondsToHoursAndMins(_time) << "." << std::endl;
        _time += 5 * MINUTE;
        _machine.moveTo(&_flowerbed); //here should be selection by index

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

Gardener::Gardener() : _flowerbed(Flowerbed(0))  { }

void Gardener::startWork() {
    _time = 0;
    while (true) {
        if (_flowerbed.couldBeWatered(_time))
            if (_flowerbed.getSensorValue() > _flowerbed.getTempLimit())
                if (!_machine.isBusy(_time)) {
                    moveMachine();
                    doWatering();
                    moveMachine(-1);
                }
        _time += 5 * MINUTE;
        std::this_thread::sleep_for(std::chrono::seconds(1));

    }

}

std::string Gardener::secondsToHoursAndMins(unsigned long seconds) {
    int minutes = seconds / 60;
    int hours = minutes / 60;
    std::stringstream str;

    str <<  int(hours) << " hours; " << int(minutes%60)
        << " minutes; " << int(seconds%60) << " seconds";
    std::string result;
    getline(str, result);
    return result;
}
