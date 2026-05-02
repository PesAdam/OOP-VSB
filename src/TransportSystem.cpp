#include "TransportSystem.h"
#include<iostream>
using namespace std;

// Konstruktor - dynamicky alokuje pole s danou kapacitou
// napr. TransportSystem system(200) vytvori system pre max 200 vozidiel
TransportSystem::TransportSystem(int capacity){
    this->fleetCapacity = capacity;
    this->fleetCount = 0;
    this->fleet = new Vehicle*[capacity];  // alokujeme pole ukazovatelov na Vehicle
}

// Destruktor - uvolni pamat
// Najprv zmazeme kazde vozidlo (delete fleet[i] zavola Bus::~Bus alebo Tram::~Tram
//   vdaka virtualnym destruktorom), potom zmazeme samotne pole
TransportSystem::~TransportSystem(){
    for(int i = 0; i < this->fleetCount; i++){
        delete this->fleet[i];   // polymorfne mazanie: zavola spravny destruktor
    }
    delete[] this->fleet;        // uvolnenie pola samotneho
}

// Prida vozidlo na dalsi volny index v poli
// Funguje polymorfne: v je Vehicle*, ale moze ukazovat na Bus aj Tram
void TransportSystem::addVehicle(Vehicle* v){
    this->fleet[this->fleetCount] = v;
    this->fleetCount++;
}

// PRETAZENA METODA 1: priradenie trasy cez hotovy objekt Route
// Vola setRoute() na vozidle, ktore si trasu skopiruje
void TransportSystem::assignRoute(Vehicle* v, Route r){
    v->setRoute(r);
}

// PRETAZENA METODA 2: priradenie trasy cez dva textove retazce
// Interne vytvori docasny objekt Route a ten priradí vozidlu
// Prekladac rozlisi tieto dve metody podla typov parametrov
void TransportSystem::assignRoute(Vehicle* v, string start, string dest){
    Route r(start, dest);   // vytvorime trasu z retazcov
    v->setRoute(r);          // priradime ju vozidlu
}

// Iteruje celu flotilu a vola drive() na kazdom vozidle
// Klucovy moment polymorfizmu:
//   fleet[i] je Vehicle*, ale za behu sa vola spravna implementacia
//   -> ak je za nim Bus, zavola sa Bus::drive()
//   -> ak je za nim Tram, zavola sa Tram::drive()
// Toto rozhodnutie nastava AZ ZA BEHU PROGRAMU (nie pri kompilacii)
void TransportSystem::startSimulation() const {
    cout << "\n=== Spustenie simulacie MHD (" << this->fleetCount << " vozidiel) ===" << endl;
    for(int i = 0; i < this->fleetCount; i++){
        this->fleet[i]->drive();   // NESKORAVA VAZBA (late binding) - polymorfne volanie
    }
    cout << "=== Simulacia ukoncena ===" << endl;
}

// Vrati ukazovatel na vozidlo na danom indexe
// Pouziva sa v main.cpp pred dynamic_cast
Vehicle* TransportSystem::getVehicle(int index) const {
    return this->fleet[index];
}

// Vrati aktualny pocet vozidiel
int TransportSystem::getFleetSize() const {
    return this->fleetCount;
}
