#include "Vehicle.h"

Vehicle::Vehicle(int id, Driver d, Route r){
    this->vehicleID = id;
    this->driver = d;
    this->route = r;
}

Vehicle::~Vehicle() {}

void Vehicle::setDriver(Driver d){ 
    this->driver = d; 
}

void Vehicle::setRoute(Route r){ 
    this->route = r; 
}

int Vehicle::getID() const { 
    return this->vehicleID; 
}

Driver Vehicle::getDriver() const { 
    return this->driver; 
}

Route Vehicle::getRoute() const { 
    return this->route; 
}
