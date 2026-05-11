#pragma once
#include<string>

// Trasa vozidla (od stanice A do stanice B). Pouziva sa ako kompozicia vo Vehicle.
class Route {
private:
    std::string startStation;
    std::string endStation;

public:
    Route();
    Route(std::string start, std::string end);
    std::string getRouteInfo() const;
    std::string getStart() const;
    std::string getEnd() const;
};

