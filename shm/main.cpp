#include <iostream>
#include <typeinfo>

#include "alcohol.hpp"
#include "cargo.hpp"
#include "fruit.hpp"
#include "island.hpp"
#include "item.hpp"
#include "map.hpp"
#include "player.hpp"
#include "ship.hpp"
#include "store.hpp"

int main() {
    Ship myShip(1000, 100, 10, "Purple Widow", 1, nullptr);
    Player player(myShip, 200, 500);
    // player.getShip()->cargo_.push_back(std::make_shared<Fruit>("Bananas", 10, 10, 6));
    // player.getShip()->cargo_.push_back(std::make_shared<Fruit>("Oranges", 14, 12, 8));
    // player.getShip()->cargo_.push_back(std::make_shared<Alcohol>("Rum", 10, 40, 50));
    // player.getShip()->cargo_.push_back(std::make_shared<Item>("Exhalibur", 1, 20, Item::Rarity::legendary));

    Store testStore{};
    testStore.generateCargo();
    testStore.listCargo();
    testStore.nextDay();
    testStore.listCargo();
    Island::Coordinates c1(0, 0);
    Island::Coordinates c2(10, 10);
    Island::Coordinates c3(3, 4);
    Island::Coordinates c4(7, 6);

    std::cout << Island::Coordinates::distance(c1, c2) << '\n';
    std::cout << Island::Coordinates::distance(c1, c3) << '\n';
    std::cout << Island::Coordinates::distance(c2, c4) << '\n';

    Fruit bananas("Bananas", 200, 10, 8);
    Fruit oranges("Oranges", 150, 12, 8);
    Fruit otherBananas("Bananas", 120, 10, 7);
    Item sword1("Excalibur", 1, 12000, Item::Rarity::legendary);
    Item sword2("Excalibur", 1, 12000, Item::Rarity::legendary);

    // testStore.purchase(&player);
    // testStore.sale(&player);

    Ship ship(1, 2, 3, "a", 2, nullptr);
    Player player(ship, 10000, 100);
    ship.setDelegate(&player);
    ship.nextDay();
    std::cout << player.getMoney();
    return 0;
}
