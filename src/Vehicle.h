#pragma once
#include "Driver.h"
#include "Route.h"

// ============================================================
// Trieda: Vehicle (Vozidlo) - ABSTRAKTNA TRIEDA
// ------------------------------------------------------------
// Zakladna trieda celej hierarchie vozidiel v systeme MHD.
// Je abstraktna, co znamena: NEMOZE byt priamo vytvorena (new Vehicle(...)).
// Musi byt rozsirena potomkom (Bus, Tram), ktory implementuje metodu drive().
//
// Dedicnost:
//   Vehicle <--- Bus
//   Vehicle <--- Tram
//
// Kompozicia (HAS-A vztah):
//   Vehicle MA vodica  (Driver driver)
//   Vehicle MA trasu   (Route route)
//
// Polymorfizmus:
//   drive() je cisto virtualna metoda -> umoznuje neskoranu vazbu (late binding)
//   Ked volame v->drive() cez Vehicle*, C++ sam rozhodne za behu programu
//   ci sa vola Bus::drive() alebo Tram::drive()
// ============================================================
class Vehicle {
protected:
    // protected = pristupne aj v potomkoch (Bus, Tram), nie zvonku
    int vehicleID;    // unikatne ID vozidla v systeme
    Driver driver;    // kompozicia: vodic priradeny k vozidlu
    Route route;      // kompozicia: trasa, po ktorej vozidlo jazdi

public:
    // Konstruktor - inicializuje ID, vodica a trasu
    Vehicle(int id, Driver d, Route r);

    // Virtualny destruktor - dolezity pri pouziti polymorfizmu!
    // Ked mazeme Bus* cez Vehicle*, zavolaju sa spravne oba destruktory
    virtual ~Vehicle();

    // CISTO VIRTUALNA METODA - kazdy potomok MUSI tuto metodu implementovat
    // Prave tato metoda zabezpecuje polymorfne spravanie (late binding)
    virtual void drive() const = 0;

    // Setter - zmeni vodica vozidla
    void setDriver(Driver d);

    // Setter - zmeni trasu vozidla (pouziva sa v TransportSystem::assignRoute)
    void setRoute(Route r);

    // Getter pre ID vozidla
    int getID() const;

    // Getter pre objekt vodica
    Driver getDriver() const;

    // Getter pre objekt trasy
    Route getRoute() const;
};
