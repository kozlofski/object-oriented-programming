#pragma once

#include <iostream>
#include <memory>
#include "cargo.hpp"
#include "ship.hpp"

class Time;
class Player : public Ship::Delegate {
public:
    Player(const std::shared_ptr<Ship> ship, size_t money, size_t availableSpace);
    Player(const std::shared_ptr<Ship> ship, size_t money);
    Player(size_t money, Time* timeObserver);

    //override from Ship::Delegate
    void PayCrew(size_t money) override;

    std::shared_ptr<Ship> getShip() const
    {
        return ship_;
    };
    size_t getMoney() const { return money_; };
    size_t getAvailableSpace() { return calcAvailableSpace(); };

    size_t getSpeed() const { return ship_->getSpeed(); };
    Cargo* getCargo(size_t index) const { return ship_->getCargo(index); };

    void setMoney(size_t newMoney) { money_ = newMoney; };

    void purchaseCargo(Cargo* cargo, size_t price, size_t amount);

private:
    std::shared_ptr<Ship> ship_{};
    size_t money_{};
    size_t availableSpace_{};  // maybe not needed ? We can get actual value only by method calcAvailableSpace()

    size_t calcAvailableSpace();
};
