#include<iostream>
#include<string>
#include "src/TransportSystem.h"
#include "src/Bus.h"
#include "src/Tram.h"
#include "src/Ticket.h"
using namespace std;

int main() {
    TransportSystem system(200);

    string stations[10] = {
        "Hlavna stanica", "Namestie slobody", "Hodzovo namestie",
        "Trnavske myto", "Mlynske nivy", "Petrzalka centrum",
        "Dlhe diely", "Kramare", "Nove Mesto", "Ruzinov"
    };

    // === Vytvorenie 100 vodicov ===
    Driver* drivers[100];
    for(int i = 0; i < 100; i++){
        drivers[i] = new Driver("Vodic_" + to_string(i + 1), 1000 + i + 1);
    }

    // === Vytvorenie 100 trase ===
    Route* routes[100];
    for(int i = 0; i < 100; i++){
        routes[i] = new Route(stations[i % 10], stations[(i + 3) % 10]);
    }

    // === Vytvorenie 50 autobusov ===
    for(int i = 0; i < 50; i++){
        double fuel = 200.0 + i * 5.0;
        Bus* bus = new Bus(i + 1, *drivers[i], *routes[i], fuel);
        system.addVehicle(bus);
    }

    // === Vytvorenie 50 elektriciek ===
    for(int i = 0; i < 50; i++){
        int voltage = 600 + (i % 3) * 150;
        Tram* tram = new Tram(i + 51, *drivers[50 + i], *routes[50 + i], voltage);
        system.addVehicle(tram);
    }

    // === Demonstracia pretazenych metod assignRoute ===
    cout << "--- Demonstracia pretazenych metod assignRoute ---" << endl;

    Vehicle* v1 = system.getVehicle(0);
    system.assignRoute(v1, Route("Safarikovo nam.", "Hviezdoslavovo nam."));
    cout << "Vozidlo #" << v1->getID()
         << " (assignRoute s objektom): " << v1->getRoute().getRouteInfo() << endl;

    Vehicle* v2 = system.getVehicle(1);
    system.assignRoute(v2, "Aupark", "Central");
    cout << "Vozidlo #" << v2->getID()
         << " (assignRoute s retazcami): " << v2->getRoute().getRouteInfo() << endl;

    // === Polymorfna simulacia ===
    system.startSimulation();

    // === Polymorfne pretypovanie ===
    cout << "\n--- Polymorfne pretypovanie (dynamic_cast) ---" << endl;
    Vehicle* ptr = system.getVehicle(0);

    Bus* busPtr = dynamic_cast<Bus*>(ptr);
    if(busPtr != nullptr){
        cout << "Uspesne pretypovanie na Bus, spustame refuel():" << endl;
        busPtr->refuel();
        cout << "Kapacita nadrze: " << busPtr->getFuelCapacity() << " L" << endl;
    }

    Tram* tramPtr = dynamic_cast<Tram*>(ptr);
    if(tramPtr == nullptr){
        cout << "Pretypovanie na Tram zlyhalo - spravny vysledok, objekt je Bus." << endl;
    }

    // === Predaj listkov ===
    cout << "\n--- Predaj cestovnych listkov ---" << endl;
    for(int i = 0; i < 250; i++){
        double price = 1.0 + (i % 5) * 0.5;
        Ticket t(price);
    }

    cout << "Celkovy pocet predanych listkov: "
         << Ticket::getTicketsCount() << endl;

    // Uvolnenie pamate vodicov a trase
    for(int i = 0; i < 100; i++){
        delete drivers[i];
        delete routes[i];
    }

    cout << "\n=== Smart MHD system ukonceny ===" << endl;
    return 0;
}
