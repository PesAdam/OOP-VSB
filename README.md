# Smart MHD System – OOP Projekt v C++

Simulácia mestskej hromadnej dopravy (MHD) demonštrujúca kľúčové koncepty objektovo orientovaného programovania v C++.

---

## Obsah

1. [Čo program robí – ľudskou rečou](#čo-program-robí--ľudskou-rečou)
2. [Štruktúra projektu](#štruktúra-projektu)
3. [UML diagram tried](#uml-diagram-tried)
4. [Popis tried](#popis-tried)
5. [OOP koncepty](#oop-koncepty)
6. [Správa pamäte](#správa-pamäte)
7. [Kompilácia a spustenie](#kompilácia-a-spustenie)

---

## Čo program robí – ľudskou rečou

Predstav si dispečing MHD v Bratislave. Máš flotilu 100 vozidiel – 50 autobusov a 50 električki. Každé vozidlo má svojho vodiča a jazdí po nejakej trase.

Program toto všetko nasimuluje:
- Vytvorí 100 vodičov a 100 trás
- Každému vozidlu priradí vodiča a trasu
- Spustí simuláciu – každé vozidlo „odchádza" a vypíše informácie o jazde
- Ukáže, ako sa dá zmeniť trasa vozidla dvoma rôznymi spôsobmi
- Ukáže, ako zistiť, či je nejaké vozidlo konkrétne autobus alebo električka
- Spočíta, koľko cestovných lístkov bolo predaných

Za všetkým stojí jeden princíp: **rozne typy vozidiel (autobus, električka) sa správajú rôzne, aj keď s nimi pracujeme rovnakým spôsobom** – to je polymorfizmus.

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

---

## UML diagram tried

> Zdrojový súbor diagramu: [`uml.puml`](uml.puml) (PlantUML – dá sa vyrenderovať na https://www.plantuml.com/plantuml)

```
┌──────────────────────────────────────┐
│           <<abstract>>               │
│              Vehicle                 │
├──────────────────────────────────────┤
│ # vehicleID    : int                 │
│ # driver       : Driver              │  ◆──────────────────► ┌─────────────┐
│ # route        : Route               │  (kompozícia)         │   Driver    │
├──────────────────────────────────────┤                       ├─────────────┤
│ + drive() : void  {abstract}         │  ◆──────────────────► │   Route     │
│ + setDriver(d)                       │  (kompozícia)         └─────────────┘
│ + setRoute(r)                        │
│ + getID() / getDriver() / getRoute() │
└────────────────┬─────────────────────┘
                 │ (dedičnosť)
        ┌────────┴────────┐
        ▼                 ▼
┌──────────────┐   ┌──────────────────┐
│     Bus      │   │      Tram        │
├──────────────┤   ├──────────────────┤
│ - fuelCap.   │   │ - pantographV.   │
├──────────────┤   ├──────────────────┤
│ + drive()    │   │ + drive()        │
│ + refuel()   │   │ + getPantoV()    │
│ + getFuelC() │   └──────────────────┘
└──────────────┘

┌────────────────────────────────────────────────┐
│               TransportSystem                  │
├────────────────────────────────────────────────┤
│ - fleet[]      : Vehicle*   (polymorfné pole)  │
│ - fleetCount   : int                           │◇────► Vehicle*
│ - fleetCapacity: int                           │  (agregácia)
├────────────────────────────────────────────────┤
│ + addVehicle(v : Vehicle*)                     │
│ + assignRoute(v, r : Route)      ──┐ pretažená │
│ + assignRoute(v, start, dest)    ──┘ metóda    │
│ + startSimulation()  [late binding]            │
│ + getVehicle(index) / getFleetSize()           │
└────────────────────────────────────────────────┘

┌─────────────────────────────────────┐
│               Ticket                │
├─────────────────────────────────────┤
│ - {static} totalTicketsCount : int  │
│ - price : double                    │
├─────────────────────────────────────┤
│ + Ticket(price)                     │
│ + getPrice() : double               │
│ + {static} getTicketsCount() : int  │  ← volá sa ako Ticket::getTicketsCount()
└─────────────────────────────────────┘
```

**Legenda vzťahov:**
- `▲` / dedičnosť (IS-A): `Bus` je `Vehicle`, `Tram` je `Vehicle`
- `◆──►` kompozícia (HAS-A): `Vehicle` vlastní `Driver` a `Route` (objekty zanikajú spolu)
- `◇──►` agregácia: `TransportSystem` spravuje `Vehicle*` (vozidlá môžu existovať samostatne)

---

## Popis tried

### `Driver` – Vodič
Jednoduchá trieda uchovávajúca meno a zamestnanecké ID vodiča. Žiadna dedičnosť. Používa sa ako **kompozícia** vo Vehicle – každé vozidlo má práve jedného vodiča.

Metódy:
- `Driver(string name, int employeeID)` – vytvorí vodiča
- `getDetails()` – vráti textový popis, napr. `"Vodic: Adam (ID: 1001)"`
- `getName()`, `getID()` – gettery

---

### `Route` – Trasa
Uchováva názov východiskovej a cieľovej zastávky. Tiež kompozícia vo Vehicle.

Metódy:
- `Route(string start, string end)` – vytvorí trasu
- `getRouteInfo()` – vráti `"Hlavna stanica -> Petrzalka centrum"`
- `getStart()`, `getEnd()` – gettery

---

### `Vehicle` – Vozidlo (abstraktná trieda)
Základ celej hierarchie. **Nemôže byť priamo inštanciovaná** (`new Vehicle(...)` nefunguje), pretože obsahuje čisto virtuálnu metódu `drive()`.

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
Rozširuje Vehicle o kapacitu palivovej nádrže (`fuelCapacity`).

Navyše oproti Vehicle:
- `fuelCapacity` – kapacita nádrže v litroch
- `drive()` – implementácia jazdy autobusu (vypíše typ, trasu, vodiča, nádrž)
- `refuel()` – simulácia dotankovania (len autobus, nie Vehicle)
- `getFuelCapacity()` – getter

---

### `Tram` – Električka (potomok Vehicle)
Rozširuje Vehicle o napätie pantografu (`pantographVoltage`).

Navyše oproti Vehicle:
- `pantographVoltage` – elektrické napätie (600V / 750V / 900V)
- `drive()` – implementácia jazdy električki
- `getPantographVoltage()` – getter

---

### `TransportSystem` – Dispečing
Centrálny správca flotily. Uchováva pole `Vehicle**` – to je kľúč k polymorfizmu: do jedného poľa vkladáme aj `Bus*` aj `Tram*`, pretože oba sú `Vehicle*`.

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
Demonštruje **statický člen triedy** – počítadlo zdieľané medzi všetkými inštanciami.

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
Bus a Tram **dedia** od Vehicle: automaticky získavajú `vehicleID`, `driver`, `route`, `getID()`, `setRoute()` atď. Samy pridávajú len to, čím sa líšia (`fuelCapacity`, `pantographVoltage`).

---

### 2. Polymorfizmus + Neskorá väzba (Late Binding)
```cpp
Vehicle* fleet[200];   // pole predkovského typu

fleet[0] = new Bus(...);    // Bus* uložený ako Vehicle*
fleet[1] = new Tram(...);   // Tram* uložený ako Vehicle*

fleet[0]->drive();   // zavolá Bus::drive()   <- rozhodnuté ZA BEHU
fleet[1]->drive();   // zavolá Tram::drive()  <- rozhodnuté ZA BEHU
```
Prekladač pri kompilácii **nevie**, čo je za `fleet[i]`. Rozhodnutie nastáva **za behu** podľa skutočného typu objektu – to je **neskorá väzba (late binding)**.

Funguje vďaka `virtual` kľúčovému slovu pri `drive()` vo Vehicle.

---

### 3. Abstraktná trieda
Vehicle je abstraktná, lebo obsahuje:
```cpp
virtual void drive() const = 0;   // = 0 znamená "čisto virtuálna"
```
Nemôžeme napísať `new Vehicle(...)`. Vždy musíme vytvoriť konkrétneho potomka (Bus alebo Tram), ktorý `drive()` implementuje.

---

### 4. Pretažené metódy (Method Overloading)
```cpp
// Verzia 1 – prijíma hotový objekt Route
system.assignRoute(v, Route("Start", "Ciel"));

// Verzia 2 – prijíma dva reťazce
system.assignRoute(v, "Start", "Ciel");
```
Rovnaké meno metódy, rôzne parametre. Prekladač rozlíši verzie podľa typov argumentov pri volaní.

---

### 5. Kompozícia (Composition – HAS-A vzťah)
Vehicle **obsahuje** Driver a Route ako priame členy (nie pointery):
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
Statická premenná existuje iba raz – patrí triede, nie konkrétnemu objektu.

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
`dynamic_cast` bezpečne overí skutočný typ objektu za behu. Ak pretypovanie dáva zmysel, vráti platný pointer. Ak nie, vráti `nullptr`.

---

## Správa pamäte

| Čo sa alokuje | Kde sa alokuje | Kde sa uvoľňuje |
|---|---|---|
| `Bus*` / `Tram*` | `main.cpp` – slučky `new Bus(...)` / `new Tram(...)` | `~TransportSystem()` – destruktor |
| `Driver*` (pole 100) | `main.cpp` | `main.cpp` – záverečné `delete drivers[i]` |
| `Route*` (pole 100) | `main.cpp` | `main.cpp` – záverečné `delete routes[i]` |
| `Vehicle*[capacity]` | `TransportSystem(int)` konštruktor | `~TransportSystem()` – `delete[] fleet` |
| `Ticket t` | `main.cpp` – stack | automaticky na konci každej iterácie slučky |

Pravidlo: **každý `new` má príslušný `delete`**.

Virtuálny destruktor vo Vehicle zabezpečí, že pri `delete fleet[i]` sa zavolá správny destruktor (`~Bus()` alebo `~Tram()`), nie len `~Vehicle()`.

---

## Kompilácia a spustenie

```bash
# Skompilovat projekt
cd projekt
make

# Spustiť
./mhd
```

Makefile kompiluje každý `.cpp` zvlášť (`-c`), potom linkuje všetky `.o` súbory do výsledného spustiteľného súboru `mhd`.

Použitý štandard: **C++17** (`-std=c++17`)
