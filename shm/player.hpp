#pragma once

#include <iostream>
#include <memory>

#include "cargo.hpp"
#include "ship.hpp"

#include <iostream>

class Player : public Ship::Delegate {
public:
    //override from Ship::Delegate
    void PayCrew(size_t money) override {
        money_ -= static_cast<int>(money);
    };

    Player(const Ship& ship, int money, size_t availableSpace);

    std::shared_ptr<Ship> getShip() const {
        return ship_;
    };
    size_t getMoney() const { return money_; };
    size_t getAvailableSpace() { return calcAvailableSpace(); };

    size_t getSpeed() const { return ship_->getSpeed(); };
    Cargo* getCargo(size_t index) const { return ship_->getCargo(index); };

    void setMoney(size_t newMoney) { money_ = newMoney; };

private:
    std::shared_ptr<Ship> ship_{};
    size_t money_{};
    size_t availableSpace_{};  // maybe not needed ? We can get actual value only by method calcAvailableSpace()

    size_t calcAvailableSpace();
};
