#include "player.hpp"

Player::Player(const Ship& ship,
               size_t money,
               size_t availableSpace)
    : ship_(std::make_shared<Ship>(ship)),
      money_(money),
      availableSpace_(availableSpace) {}

size_t Player::calcAvailableSpace() {
    size_t spaceOccupied = 0;
    for (const auto el : ship_->getCargos()) {
        spaceOccupied += el->getAmount();
    }
    availableSpace_ = ship_->getCapacity() - spaceOccupied;  // maybe assigning to this private field is not needed -
    // - only calculate & return?
    // and method would remain const, as earlier

    return availableSpace_;
}
