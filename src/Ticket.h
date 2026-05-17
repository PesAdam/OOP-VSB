#pragma once

// Trieda v roli objektu – static clen je zdielany medzi vsetkymi instanciami
class Ticket {
    static int totalTicketsCount;
    double price;                  // kazdy listok ma svoju cenu
public:
    Ticket(double price);          // zvysi totalTicketsCount o 1
    double getPrice() const;       // instancna metoda – vracia cenu konkretneho listka
    static int getTicketsCount();  // staticka metoda – volame bez instancie: Ticket::getTicketsCount()
};