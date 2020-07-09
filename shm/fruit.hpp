#pragma once
#include "cargo.hpp"

constexpr size_t expiryDate_{10};

class Time;
class Fruit : public Cargo {
public:
    Fruit(std::string name, size_t amount, size_t basePrice, Time* timeObserver, size_t timeToExpire);

    //Override from Time::IObserver
    ~Fruit() override = default;

    std::string getName() const override { return name_; }
    size_t getAmount() const override { return amount_; }
    size_t getBasePrice() const override { return basePrice_; }
    size_t getPrice() const override { return basePrice_ * timeToExpire_ / expiryDate_; }
    size_t getTimeToExpire() const { return timeToExpire_; }

    //override from Time::IObserver
    void nextDay() override;

private:
    size_t timeToExpire_{};

    Fruit& operator--();  // private? kyrtaq`s response: private!

    // override from Cargo
    bool equals(const Cargo& rhs) const override;
};
