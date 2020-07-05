#include "store.hpp"

#include <algorithm>
#include <memory>
#include <random>

#include "alcohol.hpp"
#include "cargo.hpp"
#include "fruit.hpp"
#include "item.hpp"

Store::Store() {}
// Store::Store(Time* time)
//     : time_(time) {}
Store::~Store() {}

void Store::nextDay() {
    assortment_.clear();
    generateCargo();
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

void Store::generateCargo() {
    std::random_device rd;
    std::mt19937 gen(rd());
    // normal distribution
    std::normal_distribution<> amount(30, 15);
    std::normal_distribution<> priceDifference(0, 2);
    std::normal_distribution<> expiry(6, 1);
    std::normal_distribution<> alcoholPower(0, 5);
    std::normal_distribution<> rarity(0, 3);

    assortment_.push_back(std::make_shared<Fruit>("Bananas", static_cast<size_t>(amount(gen)), 10 + static_cast<size_t>(priceDifference(gen)), static_cast<size_t>(expiry(gen))));
    assortment_.push_back(std::make_shared<Fruit>("Oranges", static_cast<size_t>(amount(gen)), 12 + static_cast<size_t>(priceDifference(gen)), static_cast<size_t>(expiry(gen))));
    assortment_.push_back(std::make_shared<Fruit>("Apples", static_cast<size_t>(amount(gen)), 14 + static_cast<size_t>(priceDifference(gen)), static_cast<size_t>(expiry(gen))));
    assortment_.push_back(std::make_shared<Fruit>("Pears", static_cast<size_t>(amount(gen)), 15 + static_cast<size_t>(priceDifference(gen)), static_cast<size_t>(expiry(gen))));

    assortment_.push_back(std::make_shared<Alcohol>("Rum", static_cast<size_t>(amount(gen)), 80 + static_cast<size_t>(priceDifference(gen)), 50 + static_cast<size_t>(alcoholPower(gen))));
    assortment_.push_back(std::make_shared<Alcohol>("Vodka", static_cast<size_t>(amount(gen)), 60 + static_cast<size_t>(priceDifference(gen)), 40 + static_cast<size_t>(alcoholPower(gen))));
    assortment_.push_back(std::make_shared<Alcohol>("Absinth", static_cast<size_t>(amount(gen)), 80 + static_cast<size_t>(priceDifference(gen)), 70 + static_cast<size_t>(alcoholPower(gen))));
    assortment_.push_back(std::make_shared<Alcohol>("Wine", static_cast<size_t>(amount(gen)), 70 + static_cast<size_t>(priceDifference(gen)), 12 + static_cast<size_t>(alcoholPower(gen))));

    assortment_.push_back(std::make_shared<Item>("Sword", 1, 100 + 10 * static_cast<size_t>(priceDifference(gen)), static_cast<Item::Rarity>(1 + std::abs(rarity(gen)))));
}

std::ostream& operator<<(std::ostream& out, const Cargo& cargo) {
    out << "-------------------------------------\n";
    out << "Cargo name: " << cargo.getName() << '\n';
    out << "Cargo amount: " << cargo.getAmount() << '\n';
    out << "Cargo baseprice: " << cargo.getBasePrice() << '\n';
    out << "-------------------------------------\n";
    return out;
}