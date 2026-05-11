#include<iostream>
#include<string>
#include<iomanip>
#include "src/TransportSystem.h"
#include "src/Bus.h"
#include "src/Tram.h"
#include "src/Ticket.h"
using namespace std;

int main() {

    TransportSystem system(50);

    string stations[6] = {
        "Hlavna stanica", "Namestie slobody", "Trnavske myto",
        "Petrzalka centrum", "Nove Mesto", "Ruzinov"
    };

    Driver* drivers[40];
    Route*  routes[40];
    for(int i = 0; i < 40; i++){
        drivers[i] = new Driver("Vodic_" + to_string(i + 1), 1000 + i + 1);
        routes[i]  = new Route(stations[i % 6], stations[(i + 2) % 6]);
    }

    for(int i = 0; i < 20; i++){
        Bus* bus = new Bus(i + 1, *drivers[i], *routes[i], 200.0 + i * 10.0);
        system.addVehicle(bus);
    }
    for(int i = 0; i < 20; i++){
        Tram* tram = new Tram(i + 21, *drivers[20 + i], *routes[20 + i], 600 + (i % 3) * 150);
        system.addVehicle(tram);
    }

    // Pretazene metody
    cout << "--- Pretazene metody assignRoute ---\n";
    Vehicle* v1 = system.getVehicle(0);
    system.assignRoute(v1, Route("Safarikovo nam.", "Hviezdoslavovo nam."));
    cout << "Vozidlo #" << v1->getID() << " (objekt Route):  " << v1->getRoute().getRouteInfo() << "\n";

    Vehicle* v2 = system.getVehicle(1);
    system.assignRoute(v2, "Aupark", "Central");
    cout << "Vozidlo #" << v2->getID() << " (dva retazce):   " << v2->getRoute().getRouteInfo() << "\n";

    // Simulacia – neskorava vazba
    cout << "\n--- Simulacia (neskorava vazba) ---\n";
    cout << left << setw(14) << "Typ"
         << setw(5)  << "ID"
         << setw(40) << "Trasa"
         << setw(18) << "Vodic"
         << "Udaj\n"
         << string(77, '-') << "\n";

    for(int i = 0; i < system.getFleetSize(); i++){
        Vehicle* v = system.getVehicle(i);
        Bus*  b = dynamic_cast<Bus*>(v);
        Tram* t = dynamic_cast<Tram*>(v);
        string typ  = b ? "AUTOBUS" : "ELEKTRICKA";
        string udaj = b ? (to_string((int)b->getFuelCapacity()) + " L")
                        : (to_string(t->getPantographVoltage()) + " V");
        cout << left
             << setw(14) << typ
             << setw(5)  << v->getID()
             << setw(40) << v->getRoute().getRouteInfo()
             << setw(18) << v->getDriver().getName()
             << udaj << "\n";
    }

    // dynamic_cast
    cout << "\n--- Polymorfne pretypovanie (dynamic_cast) ---\n";
    Vehicle* ptr = system.getVehicle(0);

    Bus* busPtr = dynamic_cast<Bus*>(ptr);
    if(busPtr != nullptr){
        cout << "dynamic_cast<Bus*>  -> uspesne\n";
        busPtr->refuel();
    }
    Tram* tramPtr = dynamic_cast<Tram*>(ptr);
    cout << "dynamic_cast<Tram*> -> "
         << (tramPtr == nullptr ? "nullptr (spravne, objekt je Bus)" : "uspesne") << "\n";

    // Staticke cleny
    cout << "\n--- Staticke cleny (Ticket) ---\n";
    for(int i = 0; i < 50; i++){
        Ticket t(1.0 + (i % 5) * 0.5);
    }
    cout << "Predanych listkov: " << Ticket::getTicketsCount() << "\n";

    for(int i = 0; i < 40; i++){
        delete drivers[i];
        delete routes[i];
    }

    return 0;
}
