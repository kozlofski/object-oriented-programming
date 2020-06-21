#include "player.hpp"

#include <numeric>

Player::Player(const Ship& ship,
               int money,
               size_t availableSpace)
    : ship_(std::make_shared<Ship>(ship)),
      money_(money),
      availableSpace_(availableSpace) {}

void Player::calculateAvailableSpace() {
    size_t availableSpace_ = ship_->getCapacity() -
                             std::accumulate(ship_->getCargo().begin(), ship_->getCargo().end(), 0,
                                             [](size_t sum, std::shared_ptr<Cargo> item) {
                                                 return sum + item->getAmount();
                                             });
}
