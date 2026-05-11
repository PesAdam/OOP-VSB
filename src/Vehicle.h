
#pragma once
#include "Driver.h"
#include "Route.h"

class Vehicle {
protected:
    int vehicleID;
    Driver driver;    
    Route route;      

public:
    Vehicle(int id, Driver d, Route r);
    virtual ~Vehicle();

    
    
    virtual void drive() const = 0;

    void setDriver(Driver d);
    void setRoute(Route r);
    int getID() const;
    Driver getDriver() const;
    Route getRoute() const;
};
