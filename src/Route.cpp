#include "Route.h"

Route::Route(){
    this->startStation = "Neznama";
    this->endStation = "Neznama";
}

Route::Route(string start, string end){
    this->startStation = start;
    this->endStation = end;
}

string Route::getRouteInfo() const {
    return this->startStation + " -> " + this->endStation;
}

string Route::getStart() const { return this->startStation; }
string Route::getEnd() const { return this->endStation; }

