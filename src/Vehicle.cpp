#include "Vehicle.h"

Vehicle::Vehicle(int id, Driver d, Route r) {
    this->vehicleID = id;
    this->driver    = d;
    this->route     = r;
}

Vehicle::~Vehicle() {}  //destruktor

void Vehicle::setRoute(Route r)                            { route = r; }
void Vehicle::setRoute(std::string start, std::string end) { route = Route(start, end); }

int    Vehicle::getID()     const { return vehicleID; }
Driver Vehicle::getDriver() const { return driver; }
Route  Vehicle::getRoute()  const { return route; }
