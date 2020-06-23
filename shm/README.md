# Symulator Handlu Morskiego - SHM

Wykorzystaj kod napisany podczas zajęć. Jeśli go nie masz to skorzystaj z kodu w katalogu [solutions](../module1/solutions)

___

## Checklist

### OOP#1

- [x] Zadanie 1 - `Cargo` - operator porównania (`operator==`)
- [x] Zadanie 2 - `Cargo` - gettery oraz konstruktor
- [x] Zadanie 3 - `Island` i `Coordinates`
- [x] Zadanie 4 - `Map` - `std::vector<Island&>` `Island* currentPosition_`
- [x] Zadanie 5 - `Map` - konstruktor bezargumentowy
- [ ] Zadanie 6 - `Map` - `Island* getIsland(const Island::Coordinates& coordinate)`
- [x] Zadanie 7 - `Player` - pola, gettery, konstruktor, podstawowe funkcje
- [ ] Zadanie 8 - `Player` - `availableSpace_`

### OOP#2

- [ ] Zadanie 1 - `Store`
- [ ] Zadanie 2 - `Alcohol`, `Fruit`, `Item` - rozszerzenie
- [ ] Zadanie 3 - `Ship`, `Cargo`, `Stock` - `nextDay()`
- [ ] Zadanie 4 - `Time` - observer
- [ ] Zadanie 5 - `friend std::ostream& operator<<`
- [ ] Zadanie 6 - `Game`
___

## Zadania

## OOP#1

### Zadanie 1

W klasie `Cargo` napisz operator porównania (`operator==`), który będzie sprawdzał, czy towary są takie same.

___

### Zadanie 2

Do klasy `Cargo` dopisz gettery oraz odpowiedni konstruktor, który wypełni wszystkie pola tej klasy.

___

### Zadanie 3

Napisz klasę `Island`, która będzie posiadała zmienną `Coordinates position_` oraz odpowiedni getter.

Klasa `Coordinates` ma określać współrzędne na mapie. Również ją napisz. Powinna przyjmować w konstruktorze 2 parametry `positionX`, `positionY` oraz operator porównania.
<!-- Klasa `Island` powinna posiadać także sklep. -->

___

### Zadanie 4

Napisz klasę `Map`, która będzie posiadała `std::vector<Island&>` przechowujący wszystkie wyspy na mapie, oraz zmienną `Island* currentPosition_` określającą aktualną pozycję gracza na mapie.

___

### Zadanie 5

W klasie `Map` utwórz konstruktor bezargumentowy, a w jego ciele utwórz 10 wysp, które przechowasz w `std::vector<Island&>`.
Do wygenerowania losowych wartości pozycji wysp na mapie skorzystaj z [przykładu na cppreference](https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution).
Wymyśl sposób, aby pozycje wysp się nie powielały.

___

### Zadanie 6

W klasie `Map` napisz funkcję

`Island* getIsland(const Island::Coordinates& coordinate)`

Powinna ona przeszukać `std::vector<Island&>` i zwrócić szukaną wyspę.

___

### Zadanie 7

Napisz klasę `Player`, która posiadać będzie 3 pola:

* `std::unique_ptr<Ship> ship_`
* `money_`
* `availableSpace_`

Dopisz także odpowiednie gettery oraz konstruktor.

Dopisz także 2 funkcje, które powinny zwracać dane ze statku:

* `size_t getSpeed() const`
* `Cargo* getCargo(size_t index) const`

___

### Zadanie 8

W klasie `Player` napisz prywatną funkcję, która obliczać będzie `availableSpace_` na podstawie aktualnej ilości towaru na statku.

___

## OOP#2


### Zadanie 1

Napisz klasę `Store`, która będzie umożliwiała dokonywanie zakupów. Wykorzystaj poniższy enum i funkcje.

```cpp
enum class Response {done, lack_of_money, lack_of_cargo, lack_of_space};

Response buy(Cargo* cargo, size_t amount, Player* player);
Response sell(Cargo* cargo, size_t amount, Player* player);
```

___

### Zadanie 2

W klasach `Alcohol`, `Fruit`, `Item` dopisz brakujące metody oraz ich implementacje.

```cpp
// override from Cargo
size_t getPrice() const override;
std::string getName() const override { return name_; }
size_t getAmount() const override { return amount_; }
size_t getBasePrice() const override { return base_price_; }
Cargo& operator+=(size_t amount) override;
Cargo& operator-=(size_t amount) override;
bool operator==(Cargo& cargo) const override;
```

___

### Zadanie 3

Dopisz do klasy `Ship`, `Cargo` oraz `Stock` metodę `nextDay()`

* Klasa `Ship`: Metoda powinna odejmować po 1 sztuce monety za każdego członka załogi.
* Klasa `Cargo`: Metoda powinna powodować psucie się towarów.
* Klasa `Stock`: Metoda powinna zmieniać ilość towaru w sklepach.

___

### Zadanie 4 (dla ambitnych)

Spróbuj napisać klasę `Time`, która będzie odpowiadać za zarządzanie czasem w grze.

Klasa ta powinna informować inne klasy, takie jak `Cargo`, `Ship`, `Stock` o upłynięciu każdego dnia.

Poczytaj czym jest wzorzec projektowy [`Observer`](https://refactoring.guru/design-patterns/observer).

___

### Zadanie 5 (dla ambitnych)

Napisz zaprzyjaźniony operator wypisywania do strumienia

```cpp
friend std::ostream& operator<<(std::ostream& out, const Store& store);
```

Ma on w przystępny sposób wypisywać towar, jaki znajduje się w danym sklepie.

___

### Zadanie 6 (dla ambitnych)

Napisz klasę `Game`, która zarządzać będzie całą rozgrywką.

Dodaj jej jedną metodę publiczną `startGame()`.

Finalnie plik main powinien wyglądać tak:

```cpp
#include "Game.hpp"

constexpr size_t start_money = 1'000;
constexpr size_t game_days = 100;
constexpr size_t final_goal = 2'000;

int main() {
    Game game(start_money, game_days, final_goal);
    game.startGame();

    return 0;
}
```
