#pragma once
#include "Driver.h"
#include "Route.h"

// [BOD 6] Zakladna trieda dedicnej hierarchie
// [BOD 8] Cisto abstraktna trieda – drive() = 0, neda sa priamo vytvorit
class Vehicle {
protected:
    int vehicleID;
    Driver driver;    // [BOD 3] Kompozicia (HAS-A): vozidlo MA vodica
    Route route;      // [BOD 3] Kompozicia (HAS-A): vozidlo MA trasu

public:
    Vehicle(int id, Driver d, Route r);
    virtual ~Vehicle();

    // [BOD 7] Neskorava vazba + [BOD 8] Cisto virtualna metoda
    // [BOD 9] Polymorfizmus – cez Vehicle* sa zavola spravna implementacia za behu
    virtual void drive() const = 0;

    void setDriver(Driver d);
    void setRoute(Route r);
    int getID() const;
    Driver getDriver() const;
    Route getRoute() const;
};
