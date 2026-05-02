#include "Tram.h"
#include<iostream>
using namespace std;

// Konstruktor - zavola konstruktor predka Vehicle(id, d, r) a priradí napatie
// : Vehicle(id, d, r) = inicializacia predkovskej casti objektu
Tram::Tram(int id, Driver d, Route r, int voltage) : Vehicle(id, d, r){
    this->pantographVoltage = voltage;
}

// Implementacia drive() pre elektrickou
// Tato metoda sa vola POLYMORFNE cez Vehicle* v TransportSystem::startSimulation()
// Vypisuje informacie o jazde: ID, trasa, vodic, napatie pantografu
void Tram::drive() const {
    cout << "[ELEKTRIČKA #" << this->vehicleID << "] "
         << "Jazda: " << this->route.getRouteInfo()
         << " | " << this->driver.getDetails()
         << " | Pantograficke napatie: " << this->pantographVoltage << " V"
         << endl;
}

// Getter pre napatie pantografu
int Tram::getPantographVoltage() const {
    return this->pantographVoltage;
}
