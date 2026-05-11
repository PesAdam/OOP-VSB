#pragma once
#include "Vehicle.h"

class Bus : public Vehicle {
private:
    double fuelCapacity;   

public:
    Bus(int id, Driver d, Route r, double fuelCapacity);

    
    
    void drive() const override;

    
    void refuel() const;
    double getFuelCapacity() const;
};
