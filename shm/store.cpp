#include "store.hpp"

#include <algorithm>
#include <memory>
#include <random>

#include "alcohol.hpp"
#include "cargo.hpp"
#include "fruit.hpp"
#include "item.hpp"

Store::Store(Time* timeObserver)
    : timeObserver_(timeObserver)
{
    if (timeObserver_) {
        timeObserver_->addObserver(this);
    }
    generateCargo();
}

Store::~Store()
{
    if (timeObserver_) {
        timeObserver_->removeObserver(this);
    }
}

void Store::nextDay()
{
    // std::cout << "Store nextDay\n";
    for (const auto& el : assortment_) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(-10, 10);
        auto diff = dist6(rd);

        if (diff < 0) {
            *(el) -= -(diff);
        }
        else {
            *(el) += diff;
        }
    }
}

Cargo* Store::getCargo(const size_t pos) const
{
    if (pos > assortment_.size()) {
        return nullptr;
    }
    return assortment_[pos].get();
}

size_t Store::getCargoBuyPrice(Cargo* cargoInStore, size_t amount) const
{
    return amount * cargoInStore->getPrice();
}

Store::Response Store::buy(Cargo* cargoInStore, size_t amount, Player* player)
{
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

    *cargoInStore -= amount;
    auto cargoToBuy = createCargo(cargoInStore, amount);
    player->purchaseCargo(cargoToBuy, totalCharge);
    return Store::Response::done;
}

Store::Response Store::sell(Cargo* cargoOnShip, size_t amount, Player* player)
{
    if (amount > cargoOnShip->getAmount()) {
        return Response::lack_of_cargo;
    }
    size_t totalCharge = amount * cargoOnShip->getPrice();
    player->setMoney(player->getMoney() + (amount * cargoOnShip->getPrice()));
    return Store::Response::done;
}

void Store::listCargo()
{
    std::for_each(assortment_.begin(), assortment_.end(), [i{1}](auto& cargo) mutable {
        std::cout << i++ << "\t" << cargo->getName() << "\t" << cargo->getPrice() << " $\t" << cargo->getAmount() << " units.\n";
    });
}

// Cargo* Store::findMatchCargo(Cargo* cargo)
// {
//     auto found = std::find(assortment_.begin(), assortment_.end(), [&cargo](auto& elem) {
//         return (elem->getName() == cargo->getName());
//     });
//     if (found != assortment_.end()) {
//         return (*found).get();
//     }
//     return nullptr;
// }

void Store::generateCargo()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<size_t> amount(15, 45);
    std::uniform_int_distribution<size_t> priceDifference(0, 4);
    std::uniform_int_distribution<size_t> expiry(6, 9);
    std::uniform_int_distribution<size_t> alcoholPower(0, 10);
    std::uniform_int_distribution<size_t> rarity(0, 3);
    std::uniform_int_distribution<size_t> amountRareItem(1, 3);

    assortment_.push_back(std::make_shared<Fruit>("Bananas",
                                                  amount(gen),
                                                  10 + priceDifference(gen),
                                                  timeObserver_,
                                                  expiry(gen)));
    assortment_.push_back(std::make_shared<Fruit>("Oranges",
                                                  amount(gen),
                                                  12 + priceDifference(gen),
                                                  timeObserver_,
                                                  expiry(gen)));
    assortment_.push_back(std::make_shared<Fruit>("Apples",
                                                  amount(gen),
                                                  14 + priceDifference(gen),
                                                  timeObserver_,
                                                  expiry(gen)));
    assortment_.push_back(std::make_shared<Fruit>("Pears",
                                                  amount(gen),
                                                  15 + priceDifference(gen),
                                                  timeObserver_,
                                                  expiry(gen)));

    assortment_.push_back(std::make_shared<Alcohol>("Rum",
                                                    amount(gen),
                                                    80 + priceDifference(gen),
                                                    timeObserver_,
                                                    45 + alcoholPower(gen)));
    assortment_.push_back(std::make_shared<Alcohol>("Vodka",
                                                    amount(gen),
                                                    60 + priceDifference(gen),
                                                    timeObserver_,
                                                    40 + alcoholPower(gen)));
    assortment_.push_back(std::make_shared<Alcohol>("Absinth",
                                                    amount(gen),
                                                    80 + priceDifference(gen),
                                                    timeObserver_,
                                                    65 + alcoholPower(gen)));
    assortment_.push_back(std::make_shared<Alcohol>("Wine",
                                                    amount(gen),
                                                    70 + priceDifference(gen),
                                                    timeObserver_,
                                                    10 + alcoholPower(gen)));

    assortment_.push_back(std::make_shared<Item>("Sword",
                                                 amountRareItem(gen),
                                                 100 + 10 * priceDifference(gen),
                                                 timeObserver_,
                                                 static_cast<Item::Rarity>(1 + rarity(gen))));
}

std::shared_ptr<Cargo> Store::createCargo(Cargo* cargo, size_t amount)
{
    if (auto* alcohol = dynamic_cast<Alcohol*>(cargo)) {
        return std::make_shared<Alcohol>(alcohol, amount);
    }
    else if (auto* fruit = dynamic_cast<Fruit*>(cargo)) {
        return std::make_shared<Fruit>(fruit, amount);
    }
    else if (auto* item = dynamic_cast<Item*>(cargo)) {
        return std::make_shared<Item>(item, amount);
    }
    return nullptr;
}
