#pragma once
#include <string>
#include "Driver.h"
#include "Route.h"
#include "IDriveable.h"

// neda sa priamo vytvorit (drive() je pure virtual)
class Vehicle : public IDriveable {
protected:
    int vehicleID;
    Driver driver;  // vozidlo ma sofera
    Route route;    // vozidlo ma trasu
public:
    Vehicle(int id, Driver d, Route r);
    virtual ~Vehicle();
    virtual void drive() const = 0;

    void setRoute(Route r);                             // pretazene metody – verzia 1
    void setRoute(std::string start, std::string end);  // pretazene metody – verzia 2
    
    int    getID()     const;
    Driver getDriver() const;  // [3] sprístupni kompozitny objekt
    Route  getRoute()  const;
};
