#pragma once
#include "Vehicle.h"

// ============================================================
// Trieda: Bus (Autobus) - POTOMOK Vehicle
// ------------------------------------------------------------
// Konkretna implementacia vozidla typu autobus.
// Dedicnostou ziskava vehicleID, driver, route a vsetky gettery z Vehicle.
// Rozsiruje predka o:
//   - fuelCapacity  (kapacita palivovej nadrze v litroch)
//   - metodu refuel() (simulacia dotankovania)
//
// Implementuje cisto virtualnu metodu drive() z Vehicle.
// Vdaka tomu mozeme Bus* ulozit do Vehicle* a cez neho polymorfne volat drive().
// ============================================================
class Bus : public Vehicle {
private:
    double fuelCapacity;   // kapacita nadrze v litroch

public:
    // Konstruktor - okrem ID, vodica a trasy (z Vehicle) prijima aj kapacitu nadrze
    Bus(int id, Driver d, Route r, double fuelCapacity);

    // Implementacia cisto virtualnej metody z Vehicle
    // override = oznacenie, ze prekryvame virtualnu metodu predka
    // Tato metoda sa vola cez Vehicle*, ked system iteruje flotilu
    void drive() const override;

    // Metoda specificka pre autobus - simuluje dotankovanie
    void refuel() const;

    // Getter pre kapacitu nadrze
    double getFuelCapacity() const;
};
