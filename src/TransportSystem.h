#pragma once
#include<string>
#include "Vehicle.h"
#include "Route.h"
using namespace std;

// ============================================================
// Trieda: TransportSystem (Dispecing MHD)
// ------------------------------------------------------------
// Centralny riadiaci system pre celu flotilu vozidiel.
// Spravuje pole ukazovatelov na vozidla (Vehicle**),
// co umoznuje polymorfne ulozenie roznych typov (Bus aj Tram)
// do jednej datovej struktury.
//
// Klucove pojmy demonostrovane touto triedou:
//   1. Polymorfna datova struktura (Vehicle** fleet)
//      -> ulozime Bus* aj Tram* do rovnakeho pola Vehicle*
//   2. Pretazene metody (method overloading) - assignRoute()
//      -> rovnake meno, rozne parametre
//   3. Neskorava vazba (late binding)
//      -> fleet[i]->drive() zavola spravnu metodu az za behu
//   4. Sprava pamate - destruktor uvolni vsetky vozidla
// ============================================================
class TransportSystem {
private:
    Vehicle** fleet;     // pole ukazovatelov na vozidla (polymorfna struktura)
    int fleetCount;      // aktualny pocet vozidiel v poli
    int fleetCapacity;   // maximalna kapacita pola (nastavena v konstruktore)

public:
    // Konstruktor - inicializuje prazdne pole s danou kapacitou
    TransportSystem(int capacity);

    // Destruktor - uvolni pamat vsetkych vozidiel aj pola
    ~TransportSystem();

    // Prida vozidlo do flotily (Bus* alebo Tram* - polymorfne)
    void addVehicle(Vehicle* v);

    // PRETAZENE metody assignRoute - rovnake meno, rozne parametre
    // Verzia 1: priradenie cez hotovy objekt Route
    void assignRoute(Vehicle* v, Route r);
    // Verzia 2: priradenie cez dva retazce (start a ciel)
    void assignRoute(Vehicle* v, string start, string dest);

    // Spusti simulaciu - iteruje flotilu a vola drive() na kazdom vozidle
    // drive() sa rezolvuje POLYMORFNE: za behu sa rozhodne Bus::drive() / Tram::drive()
    void startSimulation() const;

    // Vrati ukazovatel na vozidlo na danom indexe (pre dynamic_cast v main)
    Vehicle* getVehicle(int index) const;

    // Vrati aktualny pocet vozidiel v systeme
    int getFleetSize() const;
};
