#include "TransportSystem.h"
#include<iostream>
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
    this->fleet[this->fleetCount++] = v;
}

// [BOD 4] Pretazena metoda 1 – priradenie cez objekt Route
void TransportSystem::assignRoute(Vehicle* v, Route r){
    v->setRoute(r);
}

// [BOD 4] Pretazena metoda 2 – priradenie cez dva retazce
void TransportSystem::assignRoute(Vehicle* v, string start, string dest){
    v->setRoute(Route(start, dest));
}

// [BOD 7][BOD 9] Neskorava vazba – drive() sa rezolvuje za behu
void TransportSystem::startSimulation() const {
    cout << "\n=== Simulacia MHD (" << this->fleetCount << " vozidiel) ===" << endl;
    for(int i = 0; i < this->fleetCount; i++)
        this->fleet[i]->drive();
    cout << "=== Simulacia ukoncena ===" << endl;
}

Vehicle* TransportSystem::getVehicle(int index) const { return this->fleet[index]; }
int TransportSystem::getFleetSize() const { return this->fleetCount; }

