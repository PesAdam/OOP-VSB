#include "Vehicle.h"

// Konstruktor - priraduje hodnoty cez this->
// Parametry su hodnotou (nie referencou), cize sa skopiruju
Vehicle::Vehicle(int id, Driver d, Route r){
    this->vehicleID = id;
    this->driver = d;
    this->route = r;
}

// Prazdny virtualny destruktor
// Musi byt virtual, inak by pri delete Bus* cez Vehicle* doslo k chybe
Vehicle::~Vehicle() {}

// Zmeni vodica vozidla
void Vehicle::setDriver(Driver d){
    this->driver = d;
}

// Zmeni trasu vozidla
// Tuto metodu vola TransportSystem::assignRoute() ked priradzuje novu trasu
void Vehicle::setRoute(Route r){
    this->route = r;
}

// Vrati ID vozidla
int Vehicle::getID() const {
    return this->vehicleID;
}

// Vrati kopiu objektu vodica
Driver Vehicle::getDriver() const {
    return this->driver;
}

// Vrati kopiu objektu trasy
Route Vehicle::getRoute() const {
    return this->route;
}
