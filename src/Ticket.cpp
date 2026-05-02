#include "Ticket.h"

int Ticket::totalTicketsCount = 0;

Ticket::Ticket(double price){
    this->price = price;
    Ticket::totalTicketsCount++;
}

double Ticket::getPrice() const {
    return this->price;
}

int Ticket::getTicketsCount(){
    return Ticket::totalTicketsCount;
}
