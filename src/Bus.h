#pragma once
#include "Vehicle.h"

// [6][7] Bus je potomkom Vehicle – rozsiruje data aj metody
// Rozsirovanie dat:    pridava fuelCapacity (kapacita nadrze)
// Rozsirovanie metod: pridava refuel() – tato metoda v predkovi Vehicle neexistuje
class Bus : public Vehicle {
    private:
        double fuelCapacity;  // kapacita palivovej nadrze v litroch – specificka pre Bus

    public:
        Bus(int id, Driver d, Route r, double fuelCapacity);

        // [7] Override – Bus implementuje drive() inak ako Tram
        // Vola sa polymorfne cez Vehicle* v simulacii
        void drive() const override;

        // [7] Metoda specificka len pre Bus – neda sa volat cez Vehicle*
        // Dostupna az po dynamic_cast<Bus*>
        void refuel() const;
        double getFuelCapacity() const;
};
