#include "player.hpp"

constexpr int k_maxCrew{100};
constexpr int k_speed{10};
constexpr size_t k_id{1};
const std::string& k_name{"Black Perl"};
constexpr int k_capacity{500};

Player::Player(const std::shared_ptr<Ship> ship, size_t money, size_t availableSpace)
    : ship_(ship),
      money_(money),
      availableSpace_(availableSpace)
{
    calcAvailableSpace();
}

Player::Player(const std::shared_ptr<Ship> ship, size_t money)
    : Player(ship, money, 0)
{
    calcAvailableSpace();
}

Player::Player(size_t money, Time* timeObserver)
    : Player(std::make_shared<Ship>(
                 k_maxCrew,
                 k_speed,
                 k_id,
                 k_name,
                 k_capacity,
                 this,
                 timeObserver),
             money,
             0)
{
    calcAvailableSpace();
}

size_t Player::calcAvailableSpace()
{
    size_t spaceOccupied = 0;
    for (const auto el : ship_->getCargos()) {
        spaceOccupied += el->getAmount();
    }
    availableSpace_ = ship_->getCapacity() - spaceOccupied;  // maybe assigning to this private field is not needed -
    // - only calculate & return?
    // and method would remain const, as earlier

    return availableSpace_;
}

void Player::PayCrew(size_t money)
{
    std::cout << "Player::PayCrew\n";
    if (money > money_) {
        money_ -= money;
    }
    else {
        money_ = 0;
    }
};
