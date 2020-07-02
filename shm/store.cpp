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
    goods_.push_back(std::make_shared<Alcohol>("Rum", 10, 40, 50));
    goods_.push_back(std::make_shared<Item>("Magic sword", 1, 20, Item::Rarity::legendary));
}

void Store::purchase(Player* player) {
    std::cout << "== Welcome to our store. Today we have:\n";
    size_t totalCargo = listCargo(goods_);
    size_t chosenCargoIndex{0};
    size_t amount{0};
    Cargo* chosenCargo;
    do {
        std::cout << "== Choose what you want to buy (by index between 0 and " << totalCargo << ") or input number > " << maxCargo_ << " to cancel\n";
        std::cin >> chosenCargoIndex;
        if (chosenCargoIndex > maxCargo_) {
            break;
        }
        chosenCargo = chooseCargoToBuy(chosenCargoIndex);
        if (chosenCargo == nullptr) {
            continue;
        };
        std::cout << "Write amount:\n";
        std::cin >> amount;
        buy(chosenCargo, amount, player);
    } while (true);
}

Cargo* Store::chooseCargoToBuy(size_t chosenCargoIndex) {
    if (chosenCargoIndex > goods_.size()) {
        std::cout << "Invalid number\n";
        return nullptr;
    }
    return goods_[chosenCargoIndex].get();
}

Store::Response Store::buy(Cargo* cargoInStore, size_t amount, Player* player) {
    if (amount > player->getAvailableSpace()) {
        std::cout << "== You don't have enough space\n";
        return Response::lack_of_space;
    }
    if (amount > cargoInStore->getAmount()) {
        std::cout << "== We don't have that big amount of " << cargoInStore->getName() << "\n";
        return Response::lack_of_cargo;
    }

    size_t totalCharge = amount * cargoInStore->getPrice();
    size_t playersMoney = player->getMoney();
    if (totalCharge > playersMoney) {
        std::cout << "== You don't have enough money to buy this\n";
        return Response::lack_of_money;
    }
    // player->getShip()->loadCargo(cargoInStore, amount);
    player->setMoney(playersMoney - totalCharge);
    std::cout << amount << " " << cargoInStore->getName() << " bought with total charge of " << totalCharge << " $\n";
    std::cout << "Money left in wallet: " << player->getMoney() << "\n";
    return Response::done;
}

void Store::sale(Player* player) {
    auto cargoOnShip = player->getShip()->getCargos();
    std::cout << "== Welcome to our store. ";
    if (cargoOnShip.size() == 0) {
        std::cout << "Your ship is empty\n";
    } else {
        std::cout << "Your cargo::\n";
        size_t totalCargo = listCargo(cargoOnShip);
        size_t chosenCargoIndex{0};
        size_t amount{0};
        Cargo* chosenCargo;
        do {
            std::cout << "== Choose what you want to sell (by index between 0 and " << totalCargo << ") or input number > " << maxCargo_ << " to cancel\n";
            std::cin >> chosenCargoIndex;
            if (chosenCargoIndex > maxCargo_) {
                break;
            }
            chosenCargo = chooseCargoToSell(cargoOnShip, chosenCargoIndex);
            if (chosenCargo == nullptr) {
                continue;
            };
            std::cout << "Write amount:\n";
            std::cin >> amount;  // add dealing with wrong number
            sell(chosenCargo, amount, player);
        } while (true);
    }
}

Cargo* Store::chooseCargoToSell(std::vector<std::shared_ptr<Cargo>> cargoOnShip, size_t chosenCargoIndex) {
    if (chosenCargoIndex > cargoOnShip.size()) {
        std::cout << "Invalid number\n";
        return nullptr;
    }
    return cargoOnShip[chosenCargoIndex].get();
}

Store::Response Store::sell(Cargo* cargoOnShip, size_t amount, Player* player) {
    if (amount > cargoOnShip->getAmount()) {
        std::cout << "== You don't have that big amount of " << cargoOnShip->getName() << "\n";
        return Response::lack_of_cargo;
    }
    size_t totalCharge = amount * cargoOnShip->getPrice();
    // player->getShip()->unloadCargo(cargoOnShip, amount);
    player->setMoney(player->getMoney() + (amount * cargoOnShip->getPrice()));
    std::cout << amount << " " << cargoOnShip->getName() << " sold for " << totalCharge << " $\n";
    std::cout << "Money left in wallet: " << player->getMoney() << "\n";
    return Response::done;
}

// this method should be replaced by friend << operator or sth
size_t Store::listCargo(std::vector<std::shared_ptr<Cargo>> cargos) {
    size_t i{0};
    std::cout << "Index\tAmount\tCargo\tPrice\n";
    for (auto& cargo : cargos) {
        std::cout << i++ << "\t" << cargo->getAmount() << "\t" << cargo->getName() << "\t" << cargo->getPrice() << " $\n";
    }
    return (i - 1);
}
