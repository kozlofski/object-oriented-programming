#include <iostream>
#include <typeinfo>

#include "cargo.hpp"
#include "fruit.hpp"
#include "island.hpp"
#include "item.hpp"
#include "map.hpp"

int main() {
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

    if (sword1 == sword2) {
        std::cout << "Same\n";
    } else {
        std::cout << "Different\n";
    }
    if (bananas == otherBananas) {
        std::cout << "Same\n";
    } else {
        std::cout << "Different\n";
    }
    if (bananas == oranges) {
        std::cout << "Same\n";

    } else {
        std::cout << "Different\n";
    }

    return 0;
}
