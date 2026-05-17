#include "Ticket.h"

int Ticket::totalTicketsCount = 0;

Ticket::Ticket(double price) {
    this->price = price;
    totalTicketsCount++;
}

double Ticket::getPrice() const {
    return price;
}

int Ticket::getTicketsCount() {
    return totalTicketsCount;
}
