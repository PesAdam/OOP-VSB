#pragma once

// [BOD 5] Trieda v roli objektu – static clen zdielany medzi vsetkymi instanciami
class Ticket {
private:
    static int totalTicketsCount;
    double price;

public:
    Ticket(double price);
    double getPrice() const;
    static int getTicketsCount();   // volanie: Ticket::getTicketsCount()
};

