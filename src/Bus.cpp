#include "Bus.h"
#include<iostream>
using namespace std;

// Konstruktor - zavola konstruktor predka Vehicle(id, d, r) a priradí kapacitu nadrze
// : Vehicle(id, d, r) = inicializacia predkovskej casti objektu
Bus::Bus(int id, Driver d, Route r, double fuelCapacity) : Vehicle(id, d, r){
    this->fuelCapacity = fuelCapacity;
}

// Implementacia drive() pre autobus
// Tato metoda sa vola POLYMORFNE cez Vehicle* v TransportSystem::startSimulation()
// Vypisuje informacie o jazde: ID, trasa, vodic, kapacita nadrze
void Bus::drive() const {
    cout << "[AUTOBUS #" << this->vehicleID << "] "
         << "Jazda: " << this->route.getRouteInfo()
         << " | " << this->driver.getDetails()
         << " | Palivova nadrz: " << this->fuelCapacity << " L"
         << endl;
}

// Metoda specificka len pre Bus - vypisuje info o dotankovani
// Tato metoda NIE je v predkovi Vehicle -> neda sa volat cez Vehicle*
// Volame ju az po dynamic_cast<Bus*> v main.cpp
void Bus::refuel() const {
    cout << "[AUTOBUS #" << this->vehicleID << "] Dotankovanie vozidla. "
         << "Kapacita nadrze: " << this->fuelCapacity << " L" << endl;
}

// Getter pre kapacitu nadrze
double Bus::getFuelCapacity() const {
    return this->fuelCapacity;
}
