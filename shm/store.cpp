#include "store.hpp"

#include <iostream>

#include "alcohol.hpp"
#include "fruit.hpp"
#include "item.hpp"
#include "player.hpp"

Store::Store() {}

void Store::generate() {
    Fruit bananas("Bananas", 1, 10, 10);
    goods_.push_back(std::make_shared<Fruit>(bananas));
    Fruit oranges("Oranges", 1, 14, 13);
    goods_.push_back(std::make_shared<Fruit>(oranges));
    Fruit pineapples("Pineapples", 1, 18, 15);
    goods_.push_back(std::make_shared<Fruit>(pineapples));
}

void Store::display() {
    for (auto& good : goods_) {
        std::cout << good->getName() << " \tprice " << good->getPrice() << "\n";
    }
}

// Cargo* cargo is a pointer to cargo in the store
Response buy(Cargo* cargo, size_t amount, Player* player) {
    size_t totalCharge = amount * cargo->getPrice();
    if (amount > player->getAvailableSpace()) {
        return Response::lack_of_space;
    }
    if (amount > cargo->getAmount()) {
        return Response::lack_of_cargo;
    }

    size_t playersMoney = player->getMoney();
    if (totalCharge > playersMoney) {
        return Response::lack_of_money;
    }
    player->setMoney(playersMoney - totalCharge);

    return Response::done;
}

Response sell(Cargo* cargo, size_t amount, Player* player) {
    if (amount > cargo->getAmount()) {
        return Response::lack_of_cargo;
    }
    player->setMoney(player->getMoney() + (amount * cargo->getPrice()));
    return Response::done;
}
