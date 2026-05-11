#include "TransportSystem.h"
#include <iostream>
using namespace std;

TransportSystem::TransportSystem(int capacity){
    this->fleetCapacity = capacity;
    this->fleetCount = 0;
    this->fleet = new Vehicle*[capacity];
}

TransportSystem::~TransportSystem(){
    for(int i = 0; i < this->fleetCount; i++)
        delete this->fleet[i];
    delete[] this->fleet;
}

void TransportSystem::addVehicle(Vehicle* v){
    if(v == nullptr) return;
    if(this->fleetCount >= this->fleetCapacity){
        cerr << "[CHYBA] Flotila je plna, vozidlo nebolo pridane." << std::endl;
        return;
    }
    this->fleet[this->fleetCount++] = v;
}

void TransportSystem::assignRoute(Vehicle* v, Route r){
    if(v == nullptr) return;
    v->setRoute(r);
}

void TransportSystem::assignRoute(Vehicle* v, string start, string dest){
    if(v == nullptr) return;
    v->setRoute(Route(start, dest));
}

void TransportSystem::startSimulation() const {
    cout << "\n=== Simulacia MHD (" << this->fleetCount << " vozidiel) ===" << std::endl;
    for(int i = 0; i < this->fleetCount; i++)
        this->fleet[i]->drive();
    cout << "=== Simulacia ukoncena ===" << endl;
}

Vehicle* TransportSystem::getVehicle(int index) const {
    if(index < 0 || index >= this->fleetCount) return nullptr;
    return this->fleet[index];
}

int TransportSystem::getFleetSize() const {
    return this->fleetCount;
}
