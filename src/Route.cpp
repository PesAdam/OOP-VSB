#include "Route.h"

// Prazdny konstruktor - pouziva sa vtedy, ked vozidlo este nema pridelenou trasu
Route::Route(){
    this->startStation = "Neznama";
    this->endStation = "Neznama";
}

// Hlavny konstruktor - nastavi nazvy oboch zastavok
Route::Route(string start, string end){
    this->startStation = start;
    this->endStation = end;
}

// Vracia textovy popis trasy, napr.: "Hlavna stanica -> Petrzalka centrum"
string Route::getRouteInfo() const {
    return this->startStation + " -> " + this->endStation;
}

// Getter - vrati nazov vychodiskovej zastavky
string Route::getStart() const {
    return this->startStation;
}

// Getter - vrati nazov cielovej zastavky
string Route::getEnd() const {
    return this->endStation;
}
