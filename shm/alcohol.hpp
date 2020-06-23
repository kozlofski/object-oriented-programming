#pragma once

#include "cargo.hpp"

constexpr size_t maxPower{96};

class Alcohol : public Cargo {
    using Cargo::Cargo;

    std::string getName() const override {
        return name_;
    }

    size_t getAmount() const override {
        return amount_;
    }

    size_t getBasePrice() const override {
        return basePrice_;
    }

    size_t getPrice() const override {
        return basePrice_ * (percentage_ / maxPower);
    }

private:
    size_t percentage_;
    bool equals(const Cargo& rhs) const override;
};
