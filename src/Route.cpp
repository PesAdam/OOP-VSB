#include "Route.h"
using namespace std;

Route::Route() {
    this->startStation = "Neznama";
    this->endStation   = "Neznama";
}

Route::Route(string start, string end) {
    this->startStation = start;
    this->endStation   = end;
}

string Route::getRouteInfo() const {
    return startStation + " -> " + endStation;
}

