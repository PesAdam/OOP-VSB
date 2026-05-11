#pragma once
#include "Vehicle.h"

#pragma once
#include "Vehicle.h"

// [BOD 6] Dedicna hierarchia – Bus je potomkom Vehicle
// [BOD 7] Rozsirenie dat (fuelCapacity) aj metod (refuel()) oproti predkovi
class Bus : public Vehicle {
private:
    double fuelCapacity;   // [BOD 7] Atribut specificky pre Bus

public:
    Bus(int id, Driver d, Route r, double fuelCapacity);

    // [BOD 7] Zmena spravania s neskoravou vazbou
    // [BOD 9] Polymorfne volanie cez Vehicle* v startSimulation()
    void drive() const override;

    // [BOD 7] Rozsirenie metod – refuel() existuje len v Bus, nie vo Vehicle
    void refuel() const;
    double getFuelCapacity() const;
};
