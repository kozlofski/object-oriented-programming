#pragma once

#include <string>

#include "cargo.hpp"

class Item : public Cargo {
public:
    enum class Rarity {
        common = 1,
        rare = 5,
        epic = 15,
        legendary = 50
    };

    Item(std::string name, size_t amount, size_t basePrice, Time* timeObserver, Rarity rarity);

    //Override from Time::IObserver
    ~Item() override = default;

    // override from Cargo
    std::string getName() const override { return name_; }
    size_t getAmount() const override { return amount_; }
    size_t getBasePrice() const override { return basePrice_; }
    size_t getPrice() const override
    {
        return basePrice_ * static_cast<int>(rarity_);
    }

    //override from Time::IObserver
    void nextDay() override;

    std::string printRarity();

private:
    Rarity rarity_{};

    // override from Cargo
    bool equals(const Cargo& rhs) const override;
};
