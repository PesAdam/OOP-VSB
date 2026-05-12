#pragma once

// [5] Trieda v roli objektu – static clen totalTicketsCount je zdielany
// medzi VSETKYMI instanciami, neexistuje zvlast pre kazdy objekt
// getTicketsCount() voláme na triede bez instancie: Ticket::getTicketsCount()
class Ticket {
    private:
        static int totalTicketsCount; // pocitadlo – jedna hodnota pre celu triedu
        double price;                 // cena konkretneho listka

    public:
        Ticket(double price); // konstruktor zvysi totalTicketsCount o 1
        double getPrice() const;
        static int getTicketsCount(); // staticka metoda vracia nam pocet ticketov
};