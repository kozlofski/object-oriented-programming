#include "cargo.hpp"

#include <iostream>

Cargo::Cargo(std::string name, size_t amount, size_t basePrice, Time* timeObserver)
    : name_(name), amount_(amount), basePrice_(basePrice), timeObserver_(timeObserver)
{
    if (timeObserver_) {
        timeObserver_->addObserver(this);
    }
}

Cargo::~Cargo()
{
    if (timeObserver_) {
        timeObserver_->removeObserver(this);
    }
}

Cargo& Cargo::operator+=(size_t amount)
{
    amount_ += amount;
    return *this;
}

Cargo& Cargo::operator-=(size_t amount)
{
    if (amount > amount_) {
        amount_ = 0;
        return *this;
    }
    amount_ -= amount;
    return *this;
}

bool Cargo::operator==(const Cargo& rhs) const
{
    return (typeid(*this).name() == typeid(rhs).name() &&
            equals(rhs));
}
