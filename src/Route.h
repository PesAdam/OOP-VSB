#pragma once
#include<string>
using namespace std;

// ============================================================
// Trieda: Route (Trasa)
// ------------------------------------------------------------
// Reprezentuje trasu vozidla - od stanice A do stanice B.
// Pouziva sa ako kompozicia vo Vehicle:
//   -> vozidlo MA priradenú trasu (nie je nou)
// Trasu mozno kedykolvek zmenit cez Vehicle::setRoute()
// ============================================================
class Route {
private:
    string startStation;   // nazov vychodiskovej zastavky
    string endStation;     // nazov cielovej zastavky

public:
    // Prazdny konstruktor - nastavi "neznamu" trasu
    // potrebny rovnako ako u Driver - Vehicle ma Route ako priamy clen
    Route();

    // Hlavny konstruktor - definuje trasu medzi dvoma stanicami
    Route(string start, string end);

    // Vrati trasu v podobe: "Zastavka A -> Zastavka B"
    string getRouteInfo() const;

    // Getter pre vychodiskovu zastavku
    string getStart() const;

    // Getter pre cielovu zastavku
    string getEnd() const;
};
