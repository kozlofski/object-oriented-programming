#include <iostream>
#include <typeinfo>

#include "cargo.hpp"
#include "fruit.hpp"
#include "map.hpp"

int main() {
    Fruit bananas("Bananas", 200, 10, 8);
    Fruit oranges("Oranges", 150, 12, 8);
    Fruit otherBananas("Bananas", 120, 10, 7);

    std::cout << typeid(bananas).name() << " " << typeid(oranges).name() << " " << typeid(otherBananas).name() << "\n";

    std::cout << bananas.getTImeToExpire() << " " << oranges.getTImeToExpire() << " " << otherBananas.getTImeToExpire() << "\n";
    std::cout << bananas.getName() << " " << oranges.getName() << " " << otherBananas.getName() << "\n";

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
