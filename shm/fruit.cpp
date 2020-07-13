#include "fruit.hpp"

#include <iostream>

Fruit::Fruit(std::string name, size_t amount, size_t basePrice, Time* timeObserver, size_t timeToExpire)
    : Cargo(name, amount, basePrice, timeObserver), timeToExpire_(timeToExpire)
{
}

Fruit& Fruit::operator--()
{
    if (timeToExpire_ == 0) {
        std::cerr << "Fruit rotten\n";
        return *this;
    }
    --timeToExpire_;
    return *this;
}

bool Fruit::equals(const Cargo& rhs) const
{
    const Fruit* rFruit = dynamic_cast<const Fruit*>(&rhs);
    if (!rFruit) {
        return false;
    }
    return (name_ == rFruit->name_ &&
            timeToExpire_ == rFruit->timeToExpire_);
}

void Fruit::nextDay()
{
    // std::cout << "Fruit nextDay\n";
    Fruit::operator--();
}
