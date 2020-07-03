#include "store.hpp"

#include <algorithm>
#include <memory>
#include <random>

#include "fruit.hpp"

Store::Store() {}
// Store::Store(Time* time)
//     : time_(time) {}
Store::~Store() {}

void Store::nextDay() {}

Cargo* Store::getCargo(const size_t pos) {
    return nullptr;
}

void Store::generateCargo() {
    std::random_device rd;
    std::mt19937 gen(rd());
    // normal distribution
    std::uniform_int_distribution<> amount(0, maxAmount);
    std::uniform_int_distribution<> priceDifference(-5, 5);
    std::uniform_int_distribution<> expiry(1, 12);

    assortment_.push_back(std::make_shared<Fruit>("Bananas", amount, static_cast<size_t>(10 + priceDifference(gen)), static_cast<size_t>(expiry(gen))));
    assortment_.push_back(std::make_shared<Fruit>("Oranges", amount, static_cast<size_t>(10 + priceDifference(gen)), static_cast<size_t>(expiry(gen))));
    assortment_.push_back(std::make_shared<Fruit>("Apples", amount, static_cast<size_t>(10 + priceDifference(gen)), static_cast<size_t>(expiry(gen))));
}

Store::Response Store::buy(Cargo* cargo, size_t amount, Player* player) {
    return Store::Response::done;
}
Store::Response Store::sell(Cargo* cargo, size_t amount, Player* player) {
    return Store::Response::done;
}

void Store::listCargo() {
    std::for_each(assortment_.begin(), assortment_.end(), [i{0}](auto& cargo) mutable {
        std::cout << i << "\t" << cargo->getName() << "\t" << cargo->getPrice() << " $\t" << cargo->getAmount() << " units\n";
    });
}

Cargo* Store::findMatchCargo(Cargo* cargo) {
    return nullptr;
}
void Store::removeFromStore(Cargo* cargo) {}
