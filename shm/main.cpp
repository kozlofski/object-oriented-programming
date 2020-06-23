#include <iostream>
#include <typeinfo>

#include "cargo.hpp"
#include "fruit.hpp"
#include "item.hpp"
#include "map.hpp"

int main() {
    Fruit bananas("Bananas", 200, 10, 8);
    Fruit oranges("Oranges", 150, 12, 8);
    Fruit otherBananas("Bananas", 120, 10, 7);

    Item sword1("Excalibur", 1, 12000, Item::Rarity::legendary);
    Item sword2("Excalibur", 1, 12000, Item::Rarity::legendary);

    if (sword1 == sword2) {
        std::cout << "Miecze ruwne\n";
    } else {
        std::cout << "Miecze nie równe sobie \n";
    }
    if (bananas == otherBananas) {
        std::cout << "Banan bananowi równy\n";
    } else {
        std::cout << "Banany nie równe sobie \n";
    }
    if (bananas == oranges) {
        std::cout << "coś nie tak\n";

    } else {
        std::cout << "Banan to nie pomarancz\n";
    }

    return 0;
}
