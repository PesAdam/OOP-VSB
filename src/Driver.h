#pragma once
#include<string>
using namespace std;

// ============================================================
// Trieda: Driver (Vodic)
// ------------------------------------------------------------
// Reprezentuje vodica priradeneho k vozidlu.
// Kazdy vodic ma svoje meno a zamestnanecke ID.
// Tato trieda sa pouziva ako kompozicia vo Vehicle:
//   -> vozidlo MA svojho vodica (nie je nim)
// ============================================================
class Driver {
private:
    string name;       // meno vodica
    int employeeID;    // unikatne zamestnanecke cislo

public:
    // Konstruktor bez parametrov - vytvori "neznameho" vodica
    // pouziva sa napr. ked Vehicle potrebuje prazdny stav
    Driver();

    // Hlavny konstruktor - vytvori vodica so menom a ID
    Driver(string name, int employeeID);

    // Vrati popis vodica v podobe: "Vodic: Meno (ID: 123)"
    string getDetails() const;

    // Getter pre meno vodica
    string getName() const;

    // Getter pre zamestnanecke ID
    int getID() const;
};
