#include "store.hpp"

#include <iostream>

#include "alcohol.hpp"
#include "fruit.hpp"
#include "item.hpp"
#include "player.hpp"

Store::Store() {}

void Store::generate() {
    goods_.push_back(std::make_shared<Fruit>("Bananas", 10, 10, 6));
    goods_.push_back(std::make_shared<Fruit>("Oranges", 10, 12, 8));
    goods_.push_back(std::make_shared<Fruit>("Apples", 10, 13, 10));
}

void Store::purchase(Player* player) {
    size_t i{0};
    std::cout << "Index\tAmount\tCargo\tPrice\n";
    for (auto& good : goods_) {
        std::cout << i++ << "\t" << good->getAmount() << "\t" << good->getName() << "\t" << good->getPrice() << " $\n";
    }
    size_t input{0};
    size_t amount{0};
    // Response response;

    std::cout << "Choose what you want to buy or press 99 to cancel\n";
    std::cin >> input;
    std::cout << "Write amount:\n";
    std::cin >> amount;  // add dealing with wrong number
    buy(getCargo(input), amount, player);
}

Cargo* Store::getCargo(size_t i) {
    if (i > goods_.size()) {
        std::cout << "Invalid number\n";
    }
    return goods_[i].get();
}

// Cargo* cargo is a pointer to cargo in the store
Response Store::buy(Cargo* cargo, size_t amount, Player* player) {
    if (amount > player->getAvailableSpace()) {
        std::cout << "You don't have enough space\n";
        return Response::lack_of_space;
    }
    if (amount > cargo->getAmount()) {
        std::cout << "We don't have that big amount\n";
        return Response::lack_of_cargo;
    }

    size_t totalCharge = amount * cargo->getPrice();
    size_t playersMoney = player->getMoney();
    if (totalCharge > playersMoney) {
        return Response::lack_of_money;
    }
    // player->getShip().loadCargo(cargo, amount);
    player->setMoney(playersMoney - totalCharge);
    return Response::done;
}

Response Store::sell(Cargo* cargo, size_t amount, Player* player) {
    if (amount > cargo->getAmount()) {
        return Response::lack_of_cargo;
    }
    player->setMoney(player->getMoney() + (amount * cargo->getPrice()));
    return Response::done;
}
