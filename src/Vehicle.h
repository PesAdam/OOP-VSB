#pragma once
#include "Driver.h"
#include "Route.h"
#include "IDriveable.h"

// [BOD 6][BOD 8] Abstraktna zakladna trieda dedicnej hierarchie
// Dedi od IDriveable – preberá kontrakt ze musi implementovat drive()
// Neda sa priamo vytvorit drive() je virtual
// Vsetky spolocne data (ID, vodic, trasa) su tu, potomkovia ich dedia automaticky

class Vehicle : public IDriveable {
    protected:
        int vehicleID;  // unikatne ID vozidla
        Driver driver;  // [BOD 3] kompozicia HAS-A: vozidlo MA vodica
        Route route;    // [BOD 3] kompozicia HAS-A: vozidlo MA trasu

    public:
        Vehicle(int id, Driver d, Route r);
        virtual ~Vehicle(); // virtualny destruktor – nutny pre spravne delete cez Vehicle*

        // [BOD 7][BOD 8] Pure virtual metoda – kazdy potomok ju MUSI implementovat po svojom
        virtual void drive() const = 0;

        void setDriver(Driver d);
        void setRoute(Route r);
        int getID() const;
        Driver getDriver() const;
        Route getRoute() const;
};
