#include "Ticket.h"

// Definicia a inicializacia statickej premennej
// Toto MUSI byt mimo triedy, v .cpp subore
// Staticka premenna je zdielana - existuje raz pre celu triedu
int Ticket::totalTicketsCount = 0;

// Konstruktor - nastavi cenu listka a zvysi celkove pocitadlo
// Ticket::totalTicketsCount++ zvysi zdielany pocitadlo (nie instancny)
Ticket::Ticket(double price){
    this->price = price;
    Ticket::totalTicketsCount++;
}

// Getter - vrati cenu tohto konkretneho listka
double Ticket::getPrice() const {
    return this->price;
}

// Staticka metoda - vracia celkovy pocet VSETKYCH vydanych listkov
// Moze byt volana bez instancie: Ticket::getTicketsCount()
int Ticket::getTicketsCount(){
    return Ticket::totalTicketsCount;
}
