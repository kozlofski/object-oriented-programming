#include <iostream>
#include <typeinfo>

#include "alcohol.hpp"
#include "cargo.hpp"
#include "fruit.hpp"
#include "item.hpp"
#include "map.hpp"
#include "player.hpp"
#include "ship.hpp"
#include "store.hpp"

int main() {
    Ship myShip(1000, 100, 10, "Purple Widow", 1);
    Player player(myShip, 200, 500);
    // player.getShip()->cargo_.push_back(std::make_shared<Fruit>("Bananas", 10, 10, 6));
    // player.getShip()->cargo_.push_back(std::make_shared<Fruit>("Oranges", 14, 12, 8));
    // player.getShip()->cargo_.push_back(std::make_shared<Alcohol>("Rum", 10, 40, 50));
    // player.getShip()->cargo_.push_back(std::make_shared<Item>("Exhalibur", 1, 20, Item::Rarity::legendary));

    Store testStore{};
    testStore.generateCargo();

    // testStore.purchase(&player);
    // testStore.sale(&player);

    return 0;
}
