#pragma once

// ============================================================
// Trieda: Ticket (Cestovny listok)
// ------------------------------------------------------------
// Reprezentuje jednorazovy cestovny listok s cenou.
// Demonstruje koncept STATICKEHO clena triedy:
//   -> totalTicketsCount je zdielany medzi VSETKYMI instanciami
//   -> kazde new Ticket(...) zvysi pocitadlo o 1
//   -> pocitadlo sa nikdy neznizuje (listky sa nesmazu)
//
// Trieda v roli objektu:
//   Ticket::getTicketsCount() - volame priamo na triede, nie na instancii
//   To znamena, ze trieda sama je "adresatom" spravy
// ============================================================
class Ticket {
private:
    // Staticka premenna - existuje iba JEDNA kopia pre celu triedu
    // (nie jedna kopia pre kazdy objekt)
    static int totalTicketsCount;

    double price;   // cena listka v EUR

public:
    // Konstruktor - nastavi cenu a automaticky zvysi globalny pocitadlo listkov
    Ticket(double price);

    // Getter pre cenu listka
    double getPrice() const;

    // Staticka metoda - vrati celkovy pocet vydanych listkov
    // Vola sa ako: Ticket::getTicketsCount()  (bez instancie!)
    static int getTicketsCount();
};
