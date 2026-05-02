#include "TransportSystem.h"
#include<iostream>
using namespace std;

TransportSystem::TransportSystem(int capacity){
    this->fleetCapacity = capacity;
    this->fleetCount = 0;
    this->fleet = new Vehicle*[capacity];
}

TransportSystem::~TransportSystem(){
    for(int i = 0; i < this->fleetCount; i++){
        delete this->fleet[i];
    }
    delete[] this->fleet;
}

void TransportSystem::addVehicle(Vehicle* v){
    this->fleet[this->fleetCount] = v;
    this->fleetCount++;
}

void TransportSystem::assignRoute(Vehicle* v, Route r){
    v->setRoute(r);
}

void TransportSystem::assignRoute(Vehicle* v, string start, string dest){
    Route r(start, dest);
    v->setRoute(r);
}

void TransportSystem::startSimulation() const {
    cout << "\n=== Spustenie simulacie MHD (" << this->fleetCount << " vozidiel) ===" << endl;
    for(int i = 0; i < this->fleetCount; i++){
        this->fleet[i]->drive();
    }
    cout << "=== Simulacia ukoncena ===" << endl;
}

Vehicle* TransportSystem::getVehicle(int index) const {
    return this->fleet[index];
}

int TransportSystem::getFleetSize() const {
    return this->fleetCount;
}
