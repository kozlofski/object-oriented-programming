#include <iostream>
#include <typeinfo>

#include "cargo.hpp"
#include "fruit.hpp"
#include "item.hpp"
#include "map.hpp"
#include "player.hpp"
#include "ship.hpp"
#include "store.hpp"

int main() {
    Ship myShip(1000, 100, 10, "Dupa", 1);
    Player player(myShip, 1000, 500);

    Store testStore{};
    testStore.generate();
    testStore.display();
    return 0;
}
