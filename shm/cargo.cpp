#include "cargo.hpp"

#include <iostream>
#include <typeinfo>

Cargo::Cargo(std::string name, size_t amount, size_t basePrice)
    : name_(name), amount_(amount), basePrice_(basePrice) {}

Cargo& Cargo::operator+=(size_t amount) {
    amount_ += amount;
    return *this;
}
Cargo& Cargo::operator-=(size_t amount) {
    amount_ -= amount;
    return *this;
}

bool Cargo::operator==(const Cargo& rhs) const {
    std::cout << "== " << typeid(this).name() << " " << typeid(rhs).name();
    return (typeid(*this).name() == typeid(rhs).name() &&
            equals(rhs));
}
