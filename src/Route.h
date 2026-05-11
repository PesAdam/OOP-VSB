#pragma once
#include<string>
using namespace std;

// Trasa vozidla (od stanice A do stanice B). Pouziva sa ako kompozicia vo Vehicle.
class Route {
private:
    string startStation;
    string endStation;

public:
    Route();
    Route(string start, string end);
    string getRouteInfo() const;
    string getStart() const;
    string getEnd() const;
};
