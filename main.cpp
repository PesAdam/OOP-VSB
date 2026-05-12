#include<iostream>
#include<string>
#include<iomanip>   // setw(), left – zarovnanie stlpcov v tabulke
#include "src/TransportSystem.h"
#include "src/Bus.h"
#include "src/Tram.h"
#include "src/Ticket.h"
using namespace std;

int main() {

    // [BOD 1][BOD 10] Vytvorenie objektov vsetkych tried
    // TransportSystem je centralny spravca flotily (kapacita 50 vozidiel)
    TransportSystem system(50);

    // Pole nazvov zastávok – pouziva sa na generovanie tras
    string stations[6] = {
        "Hlavna stanica", "Namestie slobody", "Trnavske myto",
        "Petrzalka centrum", "Nove Mesto", "Ruzinov"
    };

    // [BOD 10] Vytvorenie 40 vodicov a 40 tras na dynamickej halде
    // Kazde vozidlo dostane vlastneho vodica a vlastnu trasu
    Driver* drivers[40];
    Route*  routes[40];
    for(int i = 0; i < 40; i++){
        drivers[i] = new Driver("Vodic_" + to_string(i + 1), 1000 + i + 1);
        routes[i]  = new Route(stations[i % 6], stations[(i + 2) % 6]);
    }   

    // [BOD 6][BOD 9] Bus* je ulozeny ako Vehicle* – polymorfne priradenie
    // TransportSystem drzi Vehicle** fleet, takze prijima Bus* aj Tram*
    for(int i = 0; i < 20; i++){
        Bus* bus = new Bus(i + 1, *drivers[i], *routes[i], 200.0 + i * 10.0);
        system.addVehicle(bus);
    }
    // [BOD 6][BOD 9] To iste pre Tram* – ulozeny ako Vehicle* v tom istom poli
    for(int i = 0; i < 20; i++){
        Tram* tram = new Tram(i + 21, *drivers[20 + i], *routes[20 + i], 600 + (i % 3) * 150);
        system.addVehicle(tram);
    }

    // [BOD 4] Pretazene metody – assignRoute ma dve verzie s roznymi parametrami
    // Prekladac sam rozlisi ktoru verziu zavolat podla typu argumentov
    cout << "--- Pretazene metody assignRoute ---\n";
    Vehicle* v1 = system.getVehicle(0);
    system.assignRoute(v1, Route("Safarikovo nam.", "Hviezdoslavovo nam.")); // verzia 1: objekt Route
    cout << "Vozidlo #" << v1->getID() << " (objekt Route):  " << v1->getRoute().getRouteInfo() << "\n";

    Vehicle* v2 = system.getVehicle(1);
    system.assignRoute(v2, "Aupark", "Central"); // verzia 2: dva retazce
    cout << "Vozidlo #" << v2->getID() << " (dva retazce):   " << v2->getRoute().getRouteInfo() << "\n";

    // [BOD 7][BOD 9] Neskorava vazba – drive() sa rezolvuje za behu
    // fleet[i] moze byt Bus alebo Tram, prekladac to nevie dopredu
    // az za behu sa podla skutocneho typu objektu zavola spravna drive()
    cout << "\n--- Simulacia (neskorava vazba) ---\n";
    cout << left << setw(14) << "Typ"
         << setw(5)  << "ID"
         << setw(40) << "Trasa"
         << setw(18) << "Vodic"
         << "Udaj\n"
         << string(77, '-') << "\n";

    for(int i = 0; i < system.getFleetSize(); i++){
        Vehicle* v = system.getVehicle(i);
        // [BOD 9] dynamic_cast zisti skutocny typ za Vehicle* pointerom
        Bus*  b = dynamic_cast<Bus*>(v);
        Tram* t = dynamic_cast<Tram*>(v);
        string typ  = b ? "AUTOBUS" : "ELEKTRICKA";
        // [BOD 7] Bus ma getFuelCapacity(), Tram ma getPantographVoltage()
        // tieto metody existuju len v potomkovi, nie v predkovi Vehicle
        string udaj = b ? (to_string((int)b->getFuelCapacity()) + " L")
                        : (to_string(t->getPantographVoltage()) + " V");
        cout << left
             << setw(14) << typ
             << setw(5)  << v->getID()
             << setw(40) << v->getRoute().getRouteInfo()
             << setw(18) << v->getDriver().getName()
             << udaj << "\n";
    }

    // [BOD 9] Polymorfne pretypovanie pomocou dynamic_cast
    // dynamic_cast overi skutocny typ za pointerom za behu
    cout << "\n--- Polymorfne pretypovanie (dynamic_cast) ---\n";
    Vehicle* ptr = system.getVehicle(0); // ptr ukazuje na Bus

    Bus* busPtr = dynamic_cast<Bus*>(ptr); // uspeje – za ptr stoji Bus
    if(busPtr != nullptr){
        cout << "dynamic_cast<Bus*>  -> uspesne\n";
        busPtr->refuel(); // refuel() existuje len v Bus
    }
    Tram* tramPtr = dynamic_cast<Tram*>(ptr); // zlyha – za ptr stoji Bus, nie Tram
    cout << "dynamic_cast<Tram*> -> "
         << (tramPtr == nullptr ? "nullptr (spravne, objekt je Bus)" : "uspesne") << "\n";

    // trieda v roli objektu – static clen totalTicketsCount
    // getTicketsCount() volame priamo na triede: Ticket::getTicketsCount()
    cout << "\n--- Staticke cleny (Ticket) ---\n";
    for(int i = 0; i < 50; i++){
        Ticket t(1.0 + (i % 5) * 0.5); // kazdy konstruktor zvysi totalTicketsCount o 1
    }
    cout << "Predanych listkov: " << Ticket::getTicketsCount() << "\n";

    // Bus* a Tram* su uvolnene v destruktore TransportSystem
    for(int i = 0; i < 40; i++){
        delete drivers[i];
        delete routes[i];
    }

    return 0;
}
