#pragma once
#include "Vehicle.h"

// rozsiruje data (fuelCapacity) aj metody (refuel)
class Bus : public Vehicle {
    private:
        double fuelCapacity;

    public:
        Bus(int id, Driver d, Route r, double fuelCapacity);
        
        void drive() const override;   // 
        
        void refuel() const;
        
        double getFuelCapacity() const;
};
