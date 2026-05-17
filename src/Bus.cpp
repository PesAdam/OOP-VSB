#include "Bus.h"
#include <iostream>
using namespace std;

Bus::Bus(int id, Driver d, Route r, double fuelCapacity) : Vehicle(id, d, r){
    this->fuelCapacity = fuelCapacity;
}

void Bus::drive() const {
    cout << "[AUTOBUS #" << vehicleID << "] " << route.getRouteInfo()
         << " | " << driver.getDetails() << " | Nadrz: " << fuelCapacity << " L\n";
}

void Bus::refuel() const {
    cout << "  refuel() -> AUTOBUS #" << vehicleID << " | nadrz: " << fuelCapacity << " L\n";
}

double Bus::getFuelCapacity() const { return fuelCapacity; }
