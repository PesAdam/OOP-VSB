#include "Driver.h"

// Prazdny konstruktor - nastavi vychodzi ("neznamy") stav
// Potrebny preto, lebo Vehicle obsahuje Driver priamo ako clen (nie pointer)
// a C++ pri vytvarani objektu musi inicializovat vsetky cleny
Driver::Driver(){
    this->name = "Neznamy";
    this->employeeID = 0;
}

// Hlavny konstruktor - priraduje meno a ID
Driver::Driver(string name, int employeeID){
    this->name = name;
    this->employeeID = employeeID;
}

// Vracia formatovany textovy popis vodica
// to_string() konvertuje int na string, aby sme mohli spajat retazce pomocou +
string Driver::getDetails() const {
    return "Vodic: " + this->name + " (ID: " + to_string(this->employeeID) + ")";
}

// Getter - vrati meno vodica
string Driver::getName() const {
    return this->name;
}

// Getter - vrati zamestnanecke ID
int Driver::getID() const {
    return this->employeeID;
}
