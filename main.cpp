#include<iostream>
#include<string>
#include "src/TransportSystem.h"
#include "src/Bus.h"
#include "src/Tram.h"
#include "src/Ticket.h"
using namespace std;

int main() {

    // [BOD 1]  Triedy: Driver, Route, Vehicle(abstraktna), Bus, Tram, TransportSystem, Ticket
    // [BOD 9]  Polymorfna datova struktura – Vehicle** fleet uklada Bus* aj Tram*
    // [BOD 10] Vytvorenie objektov vsetkych tried
    TransportSystem system(50);

    string stations[6] = {
        "Hlavna stanica", "Namestie slobody", "Trnavske myto",
        "Petrzalka centrum", "Nove Mesto", "Ruzinov"
    };

    // 40 vodicov a 40 tras (jeden na vozidlo)
    Driver* drivers[40];
    Route*  routes[40];
    for(int i = 0; i < 40; i++){
        drivers[i] = new Driver("Vodic_" + to_string(i + 1), 1000 + i + 1);
        routes[i]  = new Route(stations[i % 6], stations[(i + 2) % 6]);
    }

    // [BOD 6][BOD 7] Bus a Tram su potomkovia Vehicle – rozsiruju data aj metody
    // [BOD 9] Polymorfne priradenie: Bus*/Tram* ulozene ako Vehicle*
    for(int i = 0; i < 20; i++){
        Bus* bus = new Bus(i + 1, *drivers[i], *routes[i], 200.0 + i * 10.0);
        system.addVehicle(bus);
    }
    for(int i = 0; i < 20; i++){
        Tram* tram = new Tram(i + 21, *drivers[20 + i], *routes[20 + i], 600 + (i % 3) * 150);
        system.addVehicle(tram);
    }

    // [BOD 4] Pretazene metody assignRoute – rovnake meno, rozne parametre
    cout << "--- Pretazene metody assignRoute ---" << endl;
    Vehicle* v1 = system.getVehicle(0);
    system.assignRoute(v1, Route("Safarikovo nam.", "Hviezdoslavovo nam."));
    cout << "Vozidlo #" << v1->getID() << " (objekt Route):  " << v1->getRoute().getRouteInfo() << endl;

    Vehicle* v2 = system.getVehicle(1);
    system.assignRoute(v2, "Aupark", "Central");
    cout << "Vozidlo #" << v2->getID() << " (dva retazce):   " << v2->getRoute().getRouteInfo() << endl;

    // [BOD 7][BOD 9] Neskorava vazba – drive() sa rezolvuje za behu (Bus::drive vs Tram::drive)
    system.startSimulation();

    // [BOD 9] Polymorfne pretypovanie
    cout << "\n--- dynamic_cast ---" << endl;
    Vehicle* ptr = system.getVehicle(0);

    Bus* busPtr = dynamic_cast<Bus*>(ptr);   // uspeje – za ptr stoji Bus
    if(busPtr != nullptr){
        busPtr->refuel();
        cout << "Kapacita nadrze: " << busPtr->getFuelCapacity() << " L" << endl;
    }
    Tram* tramPtr = dynamic_cast<Tram*>(ptr);   // zlyha – za ptr stoji Bus, nie Tram
    if(tramPtr == nullptr)
        cout << "Pretypovanie na Tram zlyhalo – spravne, objekt je Bus." << endl;

    // [BOD 5] Trieda v roli objektu – static clen + static metoda volana na triede
    cout << "\n--- Cestovne listky ---" << endl;
    for(int i = 0; i < 50; i++){
        Ticket t(1.0 + (i % 5) * 0.5);   // [BOD 10] objekty triedy Ticket
    }
    cout << "Celkovy pocet listkov: " << Ticket::getTicketsCount() << endl;

    for(int i = 0; i < 40; i++){
        delete drivers[i];
        delete routes[i];
    }

    cout << "\n=== MHD system ukonceny ===" << endl;
    return 0;
}

