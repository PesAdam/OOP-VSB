#include "Bus.h"
#include<iostream>
using namespace std;

Bus::Bus(int id, Driver d, Route r, double fuelCapacity) : Vehicle(id, d, r){
    this->fuelCapacity = fuelCapacity;
}
void Bus::drive() const {
    cout << "[AUTOBUS #" << this->vehicleID << "] "
         << this->route.getRouteInfo()
         << " | " << this->driver.getDetails()
         << " | Nadrz: " << this->fuelCapacity << " L" << endl;
}
void Bus::refuel() const {
    cout << "  refuel() -> AUTOBUS #" << this->vehicleID
         << " | nadrz: " << this->fuelCapacity << " L" << endl;
}

double Bus::getFuelCapacity() const { return this->fuelCapacity; }
