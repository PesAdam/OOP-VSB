#include <iostream>
#include "src/Bus.h"
#include "src/Tram.h"
#include "src/Ticket.h"
using namespace std;

int main() {

    // polymorfna struktura – fleet drzi Bus* aj Tram* ako Vehicle*
    Vehicle* flotila[20];
    int count = 0;

    for (int i = 0; i < 10; i++) {
        flotila[count++] = new Bus(                                    // polymorfne priradenie Bus* -> Vehicle*
            i + 1,
            Driver("Vodic_" + to_string(i + 1), 1000 + i),                          // kompozicia – Driver je clen Vehicle
            Route("Zastavka_" + to_string(i + 1), "Zastavka_" + to_string(i + 3)),  // kompozicia – Route je clen Vehicle
            200.0 + i * 10);
        flotila[count++] = new Tram(                                   // polymorfne priradenie Tram* -> Vehicle*
            10 + i + 1,
            Driver("Vodic_" + to_string(11 + i), 2000 + i),
            Route("Sever_" + to_string(i + 1), "Juh_" + to_string(i + 3)),
            600 + (i % 3) * 150);
    }

    // Pretazene metody – setRoute ma dve verzie s roznymi parametrami
    flotila[0]->setRoute(Route("Safarikovo", "Hviezdoslavovo")); // verzia 1: objekt Route
    flotila[1]->setRoute("Aupark", "Central");                   // verzia 2: dva retazce
    
    cout << "--- Pretazene setRoute ---\n";
    cout << "flotila[0]: " << flotila[0]->getRoute().getRouteInfo() << "\n";
    cout << "flotila[1]: " << flotila[1]->getRoute().getRouteInfo() << "\n";

    // Neskora vazba - kazde vozidlo vie jazdit po svojom – spravna drive() sa vyberie az za behu
    cout << "\n--- Simulacia (neskorava vazba) ---\n";
    for (int i = 0; i < count; i++)
        flotila[i]->drive();

    // Trieda v roli objektu – staticky clen Ticket::totalTicketsCount
    cout << "\n--- Ticket (staticke cleny) ---\n";
    for (int i = 0; i < 20; i++) Ticket t(1.0 + i * 0.5);
    Ticket posledny(9.99);
    cout << "Cena listka (instancna metoda): " << posledny.getPrice() << " EUR\n";
    cout << "Predanych listkov (staticka metoda): " << Ticket::getTicketsCount() << "\n";


    for (int i = 0; i < count; i++) delete flotila[i];
    return 0;
}

