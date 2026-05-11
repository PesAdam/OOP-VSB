
#pragma once
class Ticket {
private:
    static int totalTicketsCount;
    double price;

public:
    Ticket(double price);
    double getPrice() const;
    static int getTicketsCount();   // volanie: Ticket::getTicketsCount()
};
