#pragma once
#include<string>
#include "Vehicle.h"
#include "Route.h"
using namespace std;

// Centralny dispecing. Spravuje polymorfnu flotilu vozidiel (Vehicle**).
class TransportSystem {
private:
    Vehicle** fleet;      // [BOD 9] Polymorfna datova struktura
    int fleetCount;
    int fleetCapacity;

public:
    TransportSystem(int capacity);
    ~TransportSystem();

    void addVehicle(Vehicle* v);

    // [BOD 4] Pretazene metody – rovnake meno, rozne parametre
    void assignRoute(Vehicle* v, Route r);
    void assignRoute(Vehicle* v, string start, string dest);

    // [BOD 7][BOD 9] Neskorava vazba – drive() sa rezolvuje za behu
    void startSimulation() const;

    Vehicle* getVehicle(int index) const;
    int getFleetSize() const;
};

