# Smart MHD System – OOP Projekt v C++

Ako projekt som si zvolil simuláciu mestskej hromadnej dopravy (MHD). Projekt demonštruje kľúčové koncepty objektovo orientovaného programovania v C++ ako sú dedičnosť, polymorfizmus, kompozíciu, pretažené metódy a statické členy.

---

## Obsah

1. [Štruktúra projektu](#štruktúra-projektu)
2. [Popis tried](#popis-tried)
3. [OOP koncepty](#oop-koncepty)
4. [Správa pamäte](#správa-pamäte)
5. [Kompilácia a spustenie](#kompilácia-a-spustenie)

---

## Štruktúra projektu

```
projekt/
├── main.cpp                  # vstupný bod programu
├── Makefile                  # pravidlá pre kompiláciu
└── src/
    ├── Driver.h / Driver.cpp         # trieda Vodič
    ├── Route.h  / Route.cpp          # trieda Trasa
    ├── Vehicle.h / Vehicle.cpp       # abstraktná trieda Vozidlo (základ hierarchie)
    ├── Bus.h    / Bus.cpp            # potomok: Autobus
    ├── Tram.h   / Tram.cpp           # potomok: Električka
    ├── TransportSystem.h / .cpp      # dispečing – správca flotily
    └── Ticket.h / Ticket.cpp         # cestovný lístok so statickým počítadlom
```

## Popis tried

### `Driver` – Vodič
Jednoduchá trieda, ktorú som vytvoril na uchovávanie mena a zamestnaneckého ID vodiča. Nemá žiadnu dedičnosť. Používam ju ako **kompozíciu** vo `Vehicle` – každé vozidlo má práve jedného vodiča.

Metódy:
- `Driver(string name, int employeeID)` – vytvorí vodiča
- `getDetails()` – vráti textový popis, napr. `"Vodic: Adam (ID: 1001)"`
- `getName()`, `getID()` – gettery

---

### `Route` – Trasa
Uchováva názov východiskovej a cieľovej zastávky. Taktiež ju používam ako kompozíciu vo `Vehicle`.

Metódy:
- `Route(string start, string end)` – vytvorí trasu
- `getRouteInfo()` – vráti `"Hlavna stanica -> Petrzalka centrum"`
- `getStart()`, `getEnd()` – gettery

---

### `Vehicle` – Vozidlo (abstraktná trieda)
Základ celej mojej hierarchie. **Nedá sa priamo vytvoriť** (`new Vehicle(...)` spôsobí chybu pri kompilácii), pretože obsahuje čisto virtuálnu metódu `drive()`. Všetky spoločné dáta (ID, vodič, trasa) som umiestnil sem, aby ich potomkovia dedili automaticky.

Obsahuje:
- `vehicleID` – unikátne ID
- `driver` – vodič (kompozícia)
- `route` – trasa (kompozícia)

Metódy:
- `virtual void drive() const = 0` – čisto virtuálna → každý potomok JU MUSÍ implementovať
- `setDriver()`, `setRoute()` – settery
- `getID()`, `getDriver()`, `getRoute()` – gettery
- `virtual ~Vehicle()` – virtuálny destruktor (nutný pre správne mazanie cez pointer)

---

### `Bus` – Autobus (potomok Vehicle)
Rozširuje `Vehicle` o kapacitu palivovej nádrže (`fuelCapacity`). Implementuje `drive()` vlastným spôsobom a navyše pridáva metódu `refuel()`, ktorá v `Vehicle` neexistuje.

Navyše oproti `Vehicle`:
- `fuelCapacity` – kapacita nádrže v litroch
- `drive()` – výpis informácií o jazde autobusu
- `refuel()` – simulácia dotankovania (dostupná len cez `Bus*`, nie cez `Vehicle*`)
- `getFuelCapacity()` – getter

---

### `Tram` – Električka (potomok Vehicle)
Rozširuje `Vehicle` o napätie pantografu (`pantographVoltage`). Rovnako ako `Bus` implementuje `drive()` po svojom.

Navyše oproti `Vehicle`:
- `pantographVoltage` – elektrické napätie (600V / 750V / 900V)
- `drive()` – výpis informácií o jazde električki
- `getPantographVoltage()` – getter

---

### `TransportSystem` – Dispečing
Centrálny správca flotily, ktorý som navrhol okolo poľa `Vehicle**`. To mi umožňuje uložiť do jednej štruktúry rôzne typy vozidiel – `Bus*` aj `Tram*` – a pracovať s nimi jednotne cez spoločný typ `Vehicle*`.

Atribúty:
- `Vehicle** fleet` – dynamické pole ukazovateľov na vozidlá
- `int fleetCount` – aktuálny počet vozidiel
- `int fleetCapacity` – maximálna kapacita

Metódy:
- `TransportSystem(int capacity)` – alokuje pole
- `~TransportSystem()` – uvoľní každé vozidlo aj samotné pole
- `addVehicle(Vehicle* v)` – pridá vozidlo do flotily
- `assignRoute(Vehicle* v, Route r)` – **pretažená** verzia 1: priradí hotovú trasu
- `assignRoute(Vehicle* v, string start, string dest)` – **pretažená** verzia 2: vytvorí trasu z reťazcov
- `startSimulation()` – iteruje flotilu a **polymorfne** volá `drive()`
- `getVehicle(int index)` – vráti pointer na vozidlo (pre `dynamic_cast`)
- `getFleetSize()` – vráti počet vozidiel

---

### `Ticket` – Cestovný lístok
Túto triedu som použil na demonštráciu **statického člena** – počítadlo `totalTicketsCount` je zdieľané medzi všetkými inštanciami a inkrementuje sa pri každom vytvorení lístka.

Atribúty:
- `static int totalTicketsCount` – celkový počet vydaných lístkov (jedna hodnota pre celú triedu)
- `double price` – cena lístka

Metódy:
- `Ticket(double price)` – pri každom volaní zvýši `totalTicketsCount` o 1
- `getPrice()` – getter pre cenu
- `static int getTicketsCount()` – volá sa bez inštancie: `Ticket::getTicketsCount()`

---

## OOP koncepty

### 1. Dedičnosť (Inheritance)
```
Vehicle  <---  Bus
Vehicle  <---  Tram
```
`Bus` a `Tram` dedia od `Vehicle`: automaticky získavajú `vehicleID`, `driver`, `route`, `getID()`, `setRoute()` atď. Každý z nich pridáva len to, čím sa od predka líši (`fuelCapacity`, resp. `pantographVoltage`).

---

### 2. Polymorfizmus + Neskorá väzba (Late Binding)
```cpp
Vehicle* fleet[50];

fleet[0] = new Bus(...);    // Bus* uložený ako Vehicle*
fleet[1] = new Tram(...);   // Tram* uložený ako Vehicle*

fleet[0]->drive();   // zavolá Bus::drive()   <- rozhodnuté ZA BEHU
fleet[1]->drive();   // zavolá Tram::drive()  <- rozhodnuté ZA BEHU
```
Prekladač pri kompilácii nevie, čo je za `fleet[i]`. Rozhodnutie nastáva **za behu** podľa skutočného typu objektu – to je **neskorá väzba (late binding)**. Funguje vďaka kľúčovému slovu `virtual` pri `drive()` vo `Vehicle`.

---

### 3. Abstraktná trieda
`Vehicle` je abstraktná, pretože obsahuje:
```cpp
virtual void drive() const = 0;   // = 0 znamená "čisto virtuálna"
```
Nedá sa napísať `new Vehicle(...)`. Vždy musím vytvoriť konkrétneho potomka (`Bus` alebo `Tram`), ktorý `drive()` implementuje.

---

### 4. Pretažené metódy (Method Overloading)
```cpp
// Verzia 1 – prijíma hotový objekt Route
system.assignRoute(v, Route("Start", "Ciel"));

// Verzia 2 – prijíma dva reťazce
system.assignRoute(v, "Start", "Ciel");
```
Obe metódy majú rovnaké meno, líšia sa typmi parametrov. Prekladač sám rozlíši, ktorú verziu zavolať.

---

### 5. Kompozícia (Composition – HAS-A vzťah)
`Vehicle` obsahuje `Driver` a `Route` ako priame členy (nie pointery):
```cpp
class Vehicle {
    Driver driver;   // vozidlo MÁ vodiča
    Route route;     // vozidlo MÁ trasu
};
```
Toto je rozdiel oproti dedičnosti (IS-A): autobus **JE** vozidlom, ale **MÁ** vodiča.

---

### 6. Statické členy (trieda v roli objektu)
```cpp
Ticket t1(1.0);   // totalTicketsCount = 1
Ticket t2(2.0);   // totalTicketsCount = 2
Ticket t3(1.5);   // totalTicketsCount = 3

Ticket::getTicketsCount();   // vráti 3 – voláme na TRIEDE, nie na inštancii
```
Statická premenná existuje iba raz pre celú triedu – nie zvlášť pre každý objekt.

---

### 7. Polymorfné pretypovanie (dynamic_cast)
```cpp
Vehicle* ptr = system.getVehicle(0);   // Vehicle* ukrývajúci Bus

Bus* busPtr = dynamic_cast<Bus*>(ptr);
if(busPtr != nullptr){
    busPtr->refuel();   // toto by cez Vehicle* nešlo, refuel() nie je v Vehicle
}

Tram* tramPtr = dynamic_cast<Tram*>(ptr);
// tramPtr == nullptr, lebo za ptr stojí Bus, nie Tram
```
`dynamic_cast` bezpečne overí skutočný typ objektu za behu. Ak pretypovanie dáva zmysel, vráti platný pointer, inak `nullptr`.

---

## Správa pamäte

| Čo sa alokuje | Kde sa alokuje | Kde sa uvoľňuje |
|---|---|---|
| `Bus*` / `Tram*` | `main.cpp` – cykly `new Bus(...)` / `new Tram(...)` | `~TransportSystem()` – destruktor |
| `Driver*` (pole 40) | `main.cpp` | `main.cpp` – záverečné `delete drivers[i]` |
| `Route*` (pole 40) | `main.cpp` | `main.cpp` – záverečné `delete routes[i]` |
| `Vehicle*[capacity]` | konštruktor `TransportSystem` | `~TransportSystem()` – `delete[] fleet` |
| `Ticket t` | `main.cpp` – stack | automaticky na konci každej iterácie cyklu |

Pravidlo, ktorého som sa držal: **každý `new` má príslušný `delete`**.

Virtuálny destruktor vo `Vehicle` zabezpečí, že pri `delete fleet[i]` sa zavolá správny destruktor (`~Bus()` alebo `~Tram()`), nie len `~Vehicle()`.

---

## Kompilácia a spustenie

```bash
cd projekt
make
./mhd
```

Makefile kompiluje každý `.cpp` zvlášť (`-c`), potom linkuje všetky `.o` súbory do výsledného spustiteľného súboru `mhd`.
