#include "item.hpp"

#include <iomanip>
#include <iostream>
#include <random>

Item::Item(std::string name, size_t amount, size_t basePrice, Time* timeObserver, Rarity rarity)
    : Cargo(name, amount, basePrice, timeObserver), rarity_(rarity) {}

Item::Item(Item* item, size_t amount)
    : Item(item->getName(), amount, item->getBasePrice(), item->timeObserver_, item->rarity_) {}

bool Item::equals(const Cargo& rhs) const
{
    const Item* rItem = dynamic_cast<const Item*>(&rhs);
    if (!rItem) {
        return false;
    }
    return (name_ == rItem->name_ &&
            basePrice_ == rItem->basePrice_ &&
            rarity_ == rItem->rarity_);
}

std::string Item::getRarityName() const
{
    switch (rarity_) {
    case Rarity::epic:
        return "epic";
    case Rarity::legendary:
        return "legendary";
    case Rarity::rare:
        return "rare";
    case Rarity::common:
    default:
        return "common";
    }
}

void Item::nextDay()
{
    // std::cout << "Item nextDay\n";
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 100);
    if (dist6(rng) > 90) {
        rarity_ = static_cast<Rarity>(static_cast<int>(rarity_) - 1);
        // std::cout << "Oh no! One of your crew member dropped your " << name_
        //           << "and it lost it`s rarity :( now it`s just " << getRarityName() << '\n';
    }
}

void Item::print() const
{
    std::cout << std::setw(10) << getName() << "   "
              << std::setw(4) << getAmount() << " units   "
              << std::setw(10) << getRarityName();
}
