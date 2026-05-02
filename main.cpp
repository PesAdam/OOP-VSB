// ============================================================
// Subor: main.cpp
// ------------------------------------------------------------
// Vstupny bod programu - demonstruje vsetky klucove OOP koncepty:
//   1. Dedicnost         - Bus a Tram su potomkami Vehicle
//   2. Polymorfizmus     - fleet[] obsahuje Bus aj Tram cez Vehicle*
//   3. Neskorava vazba   - drive() sa rezolvuje az za behu programu
//   4. Pretazene metody  - assignRoute() ma 2 verzie
//   5. Staticke cleny    - Ticket::getTicketsCount() bez instancie
//   6. dynamic_cast      - bezpecne pretypovanie predka na potomka
//   7. Sprava pamate     - new/delete pre vsetky dynamicke objekty
// ============================================================

#include<iostream>
#include<string>
#include "src/TransportSystem.h"
#include "src/Bus.h"
#include "src/Tram.h"
#include "src/Ticket.h"
using namespace std;

int main() {

    // Vytvorime centralny dispecing s kapacitou 200 vozidiel
    // TransportSystem interne alokuje pole Vehicle*[200]
    TransportSystem system(200);

    // Pole nazvov zastavok - pouzijeme modulo (%) pre cyklicke priradzovanie tras
    string stations[10] = {
        "Hlavna stanica", "Namestie slobody", "Hodzovo namestie",
        "Trnavske myto", "Mlynske nivy", "Petrzalka centrum",
        "Dlhe diely", "Kramare", "Nove Mesto", "Ruzinov"
    };

    // === Vytvorenie 100 vodicov ===
    // Kazdy vodic ma meno "Vodic_N" a ID 1001..1100
    // Ukladame ich ako ukazovatel, lebo objekty odovzdavame do Bus/Tram hodnotou (kopia)
    Driver* drivers[100];
    for(int i = 0; i < 100; i++){
        drivers[i] = new Driver("Vodic_" + to_string(i + 1), 1000 + i + 1);
    }

    // === Vytvorenie 100 tras ===
    // Modulo (%) zabezpeci cyklicke prechadzanie posom zastavok
    // Napr. i=0: "Hlavna stanica" -> "Trnavske myto"  (0 -> 3)
    //        i=8: "Nove Mesto"    -> "Namestie slobody" (8 -> 11%10 = 1)
    Route* routes[100];
    for(int i = 0; i < 100; i++){
        routes[i] = new Route(stations[i % 10], stations[(i + 3) % 10]);
    }

    // === Vytvorenie 50 autobusov (Bus) ===
    // Polymorfne priradenie: Bus* sa ulozi do fleet[] ako Vehicle*
    // *drivers[i] a *routes[i] = dereferencujeme pointer, odovzdame kopiu objektu
    for(int i = 0; i < 50; i++){
        double fuel = 200.0 + i * 5.0;   // kapacita nadrze: 200L az 445L
        Bus* bus = new Bus(i + 1, *drivers[i], *routes[i], fuel);
        system.addVehicle(bus);   // bus (Bus*) sa ulozi ako Vehicle* - polymorfizmus
    }

    // === Vytvorenie 50 elektriciek (Tram) ===
    // Napatie strida medzi 600V, 750V a 900V podla modulo 3
    for(int i = 0; i < 50; i++){
        int voltage = 600 + (i % 3) * 150;   // 600V | 750V | 900V
        Tram* tram = new Tram(i + 51, *drivers[50 + i], *routes[50 + i], voltage);
        system.addVehicle(tram);   // tram (Tram*) sa ulozi ako Vehicle* - polymorfizmus
    }

    // === Demonstracia PRETAZENYCH metod assignRoute ===
    // Prekladac rozlisi obe verzie podla typov argumentov:
    //   assignRoute(v, Route(...))         -> verzia s objektom
    //   assignRoute(v, string, string)     -> verzia s retazcami
    cout << "--- Demonstracia pretazenych metod assignRoute ---" << endl;

    // Verzia 1: odovzdame hotovy objekt Route
    Vehicle* v1 = system.getVehicle(0);
    system.assignRoute(v1, Route("Safarikovo nam.", "Hviezdoslavovo nam."));
    cout << "Vozidlo #" << v1->getID()
         << " (assignRoute s objektom): " << v1->getRoute().getRouteInfo() << endl;

    // Verzia 2: odovzdame dva retazce, TransportSystem si Route vytvori sam
    Vehicle* v2 = system.getVehicle(1);
    system.assignRoute(v2, "Aupark", "Central");
    cout << "Vozidlo #" << v2->getID()
         << " (assignRoute s retazcami): " << v2->getRoute().getRouteInfo() << endl;

    // === Polymorfna simulacia - NESKORAVA VAZBA ===
    // Interne vola fleet[i]->drive() v cykle
    // Prekladac NEVIE za kompilacie, ci sa zavola Bus::drive() alebo Tram::drive()
    // Toto rozhodnutie nastava AZ ZA BEHU - to je neskorava vazba (late binding)
    system.startSimulation();

    // === Polymorfne PRETYPOVANIE (dynamic_cast) ===
    // dynamic_cast<Bus*>(ptr) sa pokusi bezpecne pretypovat Vehicle* na Bus*
    // Ak za ukazovatelom stoji skutocny Bus objekt -> uspech, vrati Bus*
    // Ak za ukazovatelom stoji Tram              -> zlyhanie, vrati nullptr
    cout << "\n--- Polymorfne pretypovanie (dynamic_cast) ---" << endl;
    Vehicle* ptr = system.getVehicle(0);   // ukazovatel na predkovsky typ (skryta Bus)

    // Pokus o pretypovanie na Bus - musi uspiet, pretoze getVehicle(0) je Bus
    Bus* busPtr = dynamic_cast<Bus*>(ptr);
    if(busPtr != nullptr){
        cout << "Uspesne pretypovanie na Bus, spustame refuel():" << endl;
        busPtr->refuel();   // refuel() existuje LEN v Bus, nie vo Vehicle
        cout << "Kapacita nadrze: " << busPtr->getFuelCapacity() << " L" << endl;
    }

    // Pokus o pretypovanie na Tram - musi zlyhat, objekt je Bus nie Tram
    Tram* tramPtr = dynamic_cast<Tram*>(ptr);
    if(tramPtr == nullptr){
        cout << "Pretypovanie na Tram zlyhalo - spravny vysledok, objekt je Bus." << endl;
    }

    // === Predaj listkov - STATICKE CLENY (trieda v roli objektu) ===
    // Kazde Ticket(price) zvysi Ticket::totalTicketsCount o 1
    // Pocitadlo je staticke -> zdielane medzi vsetkymi instanciami
    cout << "\n--- Predaj cestovnych listkov ---" << endl;
    for(int i = 0; i < 250; i++){
        double price = 1.0 + (i % 5) * 0.5;   // ceny: 1.0 | 1.5 | 2.0 | 2.5 | 3.0 EUR
        Ticket t(price);   // objekt na stacku - zanikne na konci iteracie, pocitadlo zostane
    }

    // Staticka metoda - voláme priamo na triede, nie na instancii
    cout << "Celkovy pocet predanych listkov: "
         << Ticket::getTicketsCount() << endl;

    // === Uvolnenie pamate ===
    // Vozidla (Bus, Tram) uz uvolni destruktor TransportSystem (~TransportSystem)
    // Vodici a trasy boli vytvorene tu -> uvolnime ich tu
    for(int i = 0; i < 100; i++){
        delete drivers[i];
        delete routes[i];
    }
    // system sa uvolni automaticky po skonceni main() (lokalna premenna na stacku)

    cout << "\n=== Smart MHD system ukonceny ===" << endl;
    return 0;
}
