#include "Bus.h"
#include<iostream>
using namespace std;

Bus::Bus(int id, Driver d, Route r, double fuelCapacity) : Vehicle(id, d, r){
    this->fuelCapacity = fuelCapacity;
}

// [BOD 7][BOD 9] Implementacia drive() – vola sa polymorfne cez Vehicle*
void Bus::drive() const {
    cout << "[AUTOBUS #" << this->vehicleID << "] "
         << this->route.getRouteInfo()
         << " | " << this->driver.getDetails()
         << " | Nadrz: " << this->fuelCapacity << " L" << endl;
}

// [BOD 7] Metoda specificka pre Bus – neda sa volat cez Vehicle*
void Bus::refuel() const {
    cout << "[AUTOBUS #" << this->vehicleID << "] Dotankovanie. "
         << "Kapacita: " << this->fuelCapacity << " L" << endl;
}

double Bus::getFuelCapacity() const { return this->fuelCapacity; }

