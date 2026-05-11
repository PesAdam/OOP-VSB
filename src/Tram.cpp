#include "Tram.h"
#include<iostream>
using namespace std;

Tram::Tram(int id, Driver d, Route r, int voltage) : Vehicle(id, d, r){
    this->pantographVoltage = voltage;
}

// [BOD 7][BOD 9] Implementacia drive() – vola sa polymorfne cez Vehicle*
void Tram::drive() const {
    cout << "[ELEKTRIČKA #" << this->vehicleID << "] "
         << this->route.getRouteInfo()
         << " | " << this->driver.getDetails()
         << " | Napatie: " << this->pantographVoltage << " V" << endl;
}

int Tram::getPantographVoltage() const { return this->pantographVoltage; }

