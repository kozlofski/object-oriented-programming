#include "cargo.hpp"

#include <iostream>

Cargo::Cargo(std::string name, size_t amount, size_t basePrice, Time* timeObserver)
    : name_(name), amount_(amount), basePrice_(basePrice), timeObserver_(timeObserver) {
    timeObserver_->AddObserver(this);
}

Cargo::~Cargo() {
    timeObserver_->RemoveObserver(this);
}

Cargo& Cargo::operator+=(size_t amount) {
    amount_ += amount;
    return *this;
}

Cargo& Cargo::operator-=(size_t amount) {
    if (amount > amount_) {
        std::cerr << "Not enough amount of this cargo!\n";
        return *this;
    }
    amount_ -= amount;
    return *this;
}

bool Cargo::operator==(const Cargo& rhs) const {
    return (typeid(*this).name() == typeid(rhs).name() &&
            equals(rhs));
}

void Cargo::NextDay() {
    std::cout << "Cargo: " << name_ << " notified!\n";
}
