#include "store.hpp"

#include <algorithm>
#include <array>
#include <memory>
#include <random>

#include "alcohol.hpp"
#include "cargo.hpp"
#include "fruit.hpp"
#include "item.hpp"

Store::Store(Time* timeObserver)
    : timeObserver_(timeObserver) {
    if (timeObserver_) {
        generateCargo();
        timeObserver_->addObserver(this);
    }
}

Store::~Store() {
    if (timeObserver_) {
        timeObserver_->removeObserver(this);
    }
}

void Store::nextDay() {
    std::cout << "Store nextDay\n";
    for (const auto& el : assortment_) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(-10, 10);
        if (auto check = dist6(rd); el->getAmount() < check) {
            *(el) -= (el->getAmount() + 1);
        }
        *(el) += dist6(rd);
    }
}

Cargo* Store::getCargo(const size_t pos) {
    if (pos > assortment_.size()) {
        return nullptr;
    }
    return assortment_[pos].get();
}

Store::Response Store::buy(Cargo* cargoInStore, size_t amount, Player* player) {
    if (amount > player->getAvailableSpace()) {
        return Response::lack_of_space;
    }
    if (amount > cargoInStore->getAmount()) {
        return Response::lack_of_cargo;
    }

    size_t totalCharge = amount * cargoInStore->getPrice();
    size_t playersMoney = player->getMoney();
    if (totalCharge > playersMoney) {
        return Response::lack_of_money;
    }
    player->setMoney(playersMoney - totalCharge);
    return Store::Response::done;
}

Store::Response Store::sell(Cargo* cargoOnShip, size_t amount, Player* player) {
    if (amount > cargoOnShip->getAmount()) {
        return Response::lack_of_cargo;
    }
    size_t totalCharge = amount * cargoOnShip->getPrice();
    player->setMoney(player->getMoney() + (amount * cargoOnShip->getPrice()));
    return Store::Response::done;
}

void Store::listCargo() {
    std::for_each(assortment_.begin(), assortment_.end(), [i{0}](auto& cargo) mutable {
        std::cout << i++ << "\t" << cargo->getName() << "\t" << cargo->getPrice() << " $\t" << cargo->getAmount() << " units.\n";
    });
}

// Cargo* Store::findMatchCargo(Cargo* cargo) {
//     auto found = std::find(assortment_.begin(), assortment_.end(), [&cargo](auto& elem) {
//         return (elem.get()->getName() == cargo->getName() &&
//                 elem.get()->getBasePrice() == cargo->getBasePrice() &&
//                 elem.get()->getPrice() == cargo->getPrice());
//     });
//     if (found != assortment_.end()) {
//         return (*found).get();
//     }
//     return nullptr;
// }

void Store::removeFromStore(Cargo* cargo) {
}

void Store::generateAssortment(std::array<Store::AssortmentPrototype, 9> ass_pro) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> basePriceDifference(0, 2);

    for (auto& cargo : ass_pro) {
        if (cargo.type_ == "Fruit") {
            std::normal_distribution<> amount(30, 15);
            std::normal_distribution<> expiry(cargo.feature_, 1);
            assortment_.push_back(std::make_shared<Fruit>(cargo.name_,
                                                          static_cast<size_t>(std::abs(amount(gen))),
                                                          cargo.basePrice_ + static_cast<size_t>(basePriceDifference(gen)),
                                                          timeObserver_,
                                                          static_cast<size_t>(std::abs(expiry(gen)))));
        }
        if (cargo.type_ == "Alcohol") {
            std::normal_distribution<> amount(15, 5);
            std::normal_distribution<> alcoholPower(cargo.feature_, 5);
            assortment_.push_back(std::make_shared<Alcohol>(cargo.name_,
                                                            static_cast<size_t>(std::abs(amount(gen))),
                                                            cargo.basePrice_ + static_cast<size_t>(basePriceDifference(gen)),
                                                            timeObserver_,
                                                            static_cast<size_t>(std::abs(alcoholPower(gen)))));
        }
        if (cargo.type_ == "Item") {
            std::normal_distribution<> rarity(0, 3);
            assortment_.push_back(std::make_shared<Item>(cargo.name_,
                                                         1,
                                                         100 + 10 * static_cast<size_t>(basePriceDifference(gen)),
                                                         timeObserver_,
                                                         static_cast<Item::Rarity>(1 + std::abs(rarity(gen)))));
        }
    }
}

void Store::generateCargo() {
    std::array<AssortmentPrototype, 9> ass_pro = {
        Store::AssortmentPrototype{"Fruit", "Bananas", 10, 8},
        Store::AssortmentPrototype{"Fruit", "Oranges", 12, 9},
        Store::AssortmentPrototype{"Fruit", "Apples", 14, 12},
        Store::AssortmentPrototype{"Fruit", "Pears", 15, 13},
        Store::AssortmentPrototype{"Alcohol", "Rum", 80, 60},
        Store::AssortmentPrototype{"Alcohol", "Vodka", 60, 45},
        Store::AssortmentPrototype{"Alcohol", "Absinth", 80, 60},
        Store::AssortmentPrototype{"Alcohol", "Wine", 70, 15},
        Store::AssortmentPrototype{"Item", "Sword", 100, 0},
    };

    generateAssortment(ass_pro);
}
