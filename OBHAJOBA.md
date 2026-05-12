# Obhajoba projektu – Smart MHD System

---

## Čo projekt robí

Program simuluje mestskú hromadnú dopravu.
Spravuje flotilu 40 vozidiel – 20 autobusov a 20 električka – každé s vlastným vodičom a trasou.
Program demonštruje všetky požadované OOP koncepty na reálnom príklade.

---

## Bod 1 – Triedy (min. 7)

**Projekt má 8 tried:**

| Trieda | Popis |
|---|---|
| `IDriveable` | čisto abstraktná trieda – interface |
| `Vehicle` | abstraktná základná trieda hierarchie |
| `Bus` | konkrétne vozidlo – autobus |
| `Tram` | konkrétne vozidlo – električka |
| `Driver` | vodič pridelený vozidlu |
| `Route` | trasa od zastávky A do zastávky B |
| `TransportSystem` | centrálny dispečing – správca flotily |
| `Ticket` | cestovný lístok so statickým počítadlom |

**Kde ukázať:** štruktúra `src/` – každá trieda má vlastný `.h` a `.cpp`

---

## Bod 2 – Popis + UML

- Textový popis: `README.md`
- UML diagram: `uml.mmd` (otvor na mermaid.live)

---

## Bod 3 – Kompozícia (HAS-A vzťah)

> „Autobus **je** vozidlo, ale **má** vodiča a trasu."

```cpp
// src/Vehicle.h
class Vehicle {
    Driver driver;   // vozidlo MÁ vodiča – nie dedičnosť, ale členská premenná
    Route route;     // vozidlo MÁ trasu  – zanikne spolu s vozidlom
};
```

**Kde ukázať:** `src/Vehicle.h` – protected sekcia, `driver` a `route` ako priame členy (nie pointery)

---

## Bod 4 – Pretažené metódy

Dve metódy s rovnakým menom, rozdielne parametre – prekladač sám rozlíši ktorú zavolať.

```cpp
// src/TransportSystem.h
void assignRoute(Vehicle* v, Route r);               // verzia 1: objekt Route
void assignRoute(Vehicle* v, string start, string dest); // verzia 2: dva reťazce
```

**Kde ukázať:** `src/TransportSystem.h` obe deklarácie, `main.cpp` – sekcia `Pretazene metody assignRoute` – volanie s `v1` aj `v2`

---

## Bod 5 – Trieda v roli objektu (statický člen)

`totalTicketsCount` existuje **raz pre celú triedu** – nie zvlášť pre každý lístok.
Každý konštruktor ho zvýši o 1. Volá sa bez inštancie priamo na triede.

```cpp
// src/Ticket.h
static int totalTicketsCount;      // jedna hodnota pre celú triedu

// main.cpp
Ticket::getTicketsCount()          // volanie na TRIEDE, nie na objekte
```

**Kde ukázať:** `src/Ticket.h` – static člen, `src/Ticket.cpp` – `totalTicketsCount++` v konštruktore, `main.cpp` – sekcia `Staticke cleny`

---

## Bod 6 – Dedičná hierarchia (min. 3 triedy)

```
IDriveable          (čisto abstraktná – interface)
    └── Vehicle     (abstraktná – má dáta, drive() = 0)
            ├── Bus     (konkrétna – implementuje drive())
            └── Tram    (konkrétna – implementuje drive())
```

`Bus` aj `Tram` automaticky dedia `vehicleID`, `driver`, `route`, `getID()`, `setRoute()` od `Vehicle`.
Každý pridáva len to, čím sa od predka líši.

**Kde ukázať:** `src/Bus.h` – `class Bus : public Vehicle`, `src/Tram.h` – `class Tram : public Vehicle`, `src/Vehicle.h` – `class Vehicle : public IDriveable`

---

## Bod 7 – Rozšírenie + zmena správania + neskorá väzba

### Rozšírenie dát:
```cpp
// Bus pridáva fuelCapacity – v predkovi Vehicle neexistuje
double fuelCapacity;

// Tram pridáva pantographVoltage – v predkovi Vehicle neexistuje
int pantographVoltage;
```

### Rozšírenie metód:
```cpp
// Bus pridáva refuel() – táto metóda v Vehicle neexistuje
// dostupná len cez Bus*, nie cez Vehicle*
busPtr->refuel();
```

### Neskorá väzba:
```cpp
// main.cpp – simulácia
Vehicle* v = system.getVehicle(i);  // za pointerom môže byť Bus alebo Tram
v->drive();                          // prekladač nevie – rozhodne sa ZA BEHU
                                     // zavolá Bus::drive() alebo Tram::drive()
```

Funguje vďaka kľúčovému slovu `virtual` pri `drive()` vo `Vehicle`.

**Kde ukázať:** `src/Vehicle.h` – `virtual void drive() const = 0`, `src/Bus.cpp` – `Bus::drive()`, `src/Tram.cpp` – `Tram::drive()`, `main.cpp` – for cyklus v simulácii

---

## Bod 8 – Čisto abstraktná trieda

`IDriveable` obsahuje **iba** pure virtual metódu, žiadne dáta – funguje ako interface:

```cpp
// src/IDriveable.h
class IDriveable {
    virtual void drive() const = 0;   // = 0 znamená "čisto virtuálna"
};
```

`new IDriveable()` → chyba pri kompilácii
`new Vehicle()` → chyba pri kompilácii
`new Bus()` → funguje – Bus implementuje drive()

**Kde ukázať:** `src/IDriveable.h` – celý súbor

---

## Bod 9 – Polymorfizmus

### Polymorfná dátová štruktúra:
```cpp
// src/TransportSystem.h
Vehicle** fleet;   // jedno pole drží Bus* aj Tram* cez spoločný typ Vehicle*
```

### Polymorfné priradenie:
```cpp
// main.cpp
Vehicle* v = new Bus(...);    // Bus* uložený ako Vehicle*
Vehicle* v = new Tram(...);   // Tram* uložený ako Vehicle*
```

### dynamic_cast – bezpečné pretypovanie za behu:
```cpp
// main.cpp – sekcia dynamic_cast
Bus* b = dynamic_cast<Bus*>(ptr);    // uspeje – za ptr stojí Bus
Tram* t = dynamic_cast<Tram*>(ptr); // vráti nullptr – za ptr stojí Bus, nie Tram
```

**Kde ukázať:** `src/TransportSystem.h` – `Vehicle** fleet`, `main.cpp` – sekcia `Polymorfne pretypovanie`

---

## Bod 10 – Počet objektov

| Trieda | Počet |
|---|---|
| `Bus` | 20 |
| `Tram` | 20 |
| `Driver` | 40 |
| `Route` | 40 |
| `Ticket` | 50 |
| `TransportSystem` | 1 |
| **Spolu** | **171** |

**Kde ukázať:** `main.cpp` – for cykly na začiatku, sekcia `Staticke cleny` pre Ticket

---

## Správa pamäte

Každý `new` má príslušný `delete`:

| Čo | Kde sa alokuje | Kde sa uvoľňuje |
|---|---|---|
| `Bus*` / `Tram*` | `main.cpp` – `new Bus(...)` | `~TransportSystem()` |
| `Driver*` (40x) | `main.cpp` | `main.cpp` – záverečný cyklus |
| `Route*` (40x) | `main.cpp` | `main.cpp` – záverečný cyklus |
| `Vehicle**` pole | konštruktor `TransportSystem` | `~TransportSystem()` |

Virtuálny destruktor vo `Vehicle` zabezpečí, že sa zavolá `~Bus()` alebo `~Tram()`, nie len `~Vehicle()`.

**Kde ukázať:** `src/TransportSystem.cpp` – `~TransportSystem()`, `src/Vehicle.h` – `virtual ~Vehicle()`

---

## Rýchly prehľad – kde čo nájsť

| Bod | Súbor | Čo ukázať |
|---|---|---|
| 1 – triedy | `src/` | každá trieda má vlastný súbor |
| 3 – kompozícia | `src/Vehicle.h` | `Driver driver; Route route;` |
| 4 – pretaženie | `src/TransportSystem.h` | obe `assignRoute` |
| 5 – static | `src/Ticket.h` + `main.cpp` | `static int totalTicketsCount` |
| 6 – hierarchia | `src/Bus.h`, `src/Vehicle.h` | `: public Vehicle` |
| 7 – neskorá väzba | `src/Vehicle.h` + `main.cpp` | `virtual drive()`, for cyklus |
| 8 – abstraktná | `src/IDriveable.h` | `= 0`, žiadne dáta |
| 9 – polymorfizmus | `src/TransportSystem.h` + `main.cpp` | `Vehicle** fleet`, `dynamic_cast` |
| 10 – objekty | `main.cpp` | cykly + výpis |
