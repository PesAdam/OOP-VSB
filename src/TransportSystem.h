
#pragma once
#include<string>
#include "Vehicle.h"
#include "Route.h"

// [BOD 9] Centralny dispecing – spravuje polymorfnu datovu strukturu Vehicle**
// Do jedneho pola mozno ulozit Bus* aj Tram* cez spolocny typ Vehicle*
class TransportSystem {
    private:
        Vehicle** fleet;   // polymorfna datova struktura – drzi Bus* aj Tram* ako Vehicle*
        int fleetCount;    // aktualny pocet vozidiel v flotile
        int fleetCapacity; // maximalna kapacita pola

    public:
        TransportSystem(int capacity);
        ~TransportSystem(); // uvolni kazde vozidlo aj samotne pole

        void addVehicle(Vehicle* v); // prida vozidlo do flotily, kontroluje kapacitu

        // [BOD 4] Pretazene metody – rovnake meno, rozne parametre
        // Prekladac sam rozlisi ktoru verziu zavolat
        void assignRoute(Vehicle* v, Route r);                          // verzia 1: hotovy objekt Route
        void assignRoute(Vehicle* v, std::string start, std::string dest); // verzia 2: dva retazce

        // [BOD 7][BOD 9] Iteruje flotilu a polymorfne vola drive() na kazdom vozidle
        void startSimulation() const;

        Vehicle* getVehicle(int index) const; // vrati pointer na vozidlo podla indexu
        int getFleetSize() const;
};
