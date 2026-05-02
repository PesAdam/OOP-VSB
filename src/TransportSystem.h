#pragma once
#include<string>
#include "Vehicle.h"
#include "Route.h"
using namespace std;

class TransportSystem {
private:
    Vehicle** fleet;
    int fleetCount;
    int fleetCapacity;

public:
    TransportSystem(int capacity);
    ~TransportSystem();

    void addVehicle(Vehicle* v);

    void assignRoute(Vehicle* v, Route r);
    void assignRoute(Vehicle* v, string start, string dest);

    void startSimulation() const;

    Vehicle* getVehicle(int index) const;
    int getFleetSize() const;
};
