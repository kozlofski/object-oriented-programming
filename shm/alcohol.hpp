#pragma once

#include "cargo.hpp"

constexpr size_t maxPower{96};

class Time;

class Alcohol : public Cargo {
public:
    Alcohol(std::string name, size_t amount, size_t basePrice, Time* timeObserver, size_t alcoholPower);

    //Override from Time::IObserver
    ~Alcohol() override = default;

    std::string getName() const override { return name_; }
    size_t getAmount() const override { return amount_; }
    size_t getBasePrice() const override { return basePrice_; }
    size_t getPrice() const override
    {
        return basePrice_ * alcoholPower_ / maxPower;
    }

    //override from Time::IObserver
    void nextDay() override;

private:
    size_t alcoholPower_{};

    //override from Cargo
    bool equals(const Cargo& rhs) const override;
};
