#include "Tram.h"
#include <iostream>
using namespace std;

Tram::Tram(int id, Driver d, Route r, int voltage) : Vehicle(id, d, r){
    this->pantographVoltage = voltage;
}

void Tram::drive() const {
    std::cout << "[ELEKTRIČKA #" << this->vehicleID << "] "
              << this->route.getRouteInfo()
              << " | " << this->driver.getDetails()
              << " | Napatie: " << this->pantographVoltage << " V" << std::endl;
}

int Tram::getPantographVoltage() const {
    return this->pantographVoltage;
}
