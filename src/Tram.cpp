#include "Tram.h"
#include <iostream>
using namespace std;

Tram::Tram(int id, Driver d, Route r, int voltage)
    : Vehicle(id, d, r)
{
    this->pantographVoltage = voltage;
}

void Tram::drive() const {
    cout << "[ELEKTRIČKA #" << vehicleID << "] " << route.getRouteInfo()
         << " | " << driver.getDetails() << " | Napatie: " << pantographVoltage << " V\n";
}

int Tram::getPantographVoltage() const { return pantographVoltage; }
