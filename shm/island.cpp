#include "island.hpp"

#include <cmath>

Island::Coordinates::Coordinates(size_t positionX, size_t positionY)
    : positionX_(positionX), positionY_(positionY) {}

bool Island::Coordinates::operator==(const Coordinates& rhs) const
{
    return ((positionX_ == rhs.positionX_) &&
            (positionY_ == rhs.positionY_));
}

size_t Island::Coordinates::distance(const Coordinates& lhs, const Coordinates& rhs)
{
    double distance =
        std::sqrt(std::pow(static_cast<long>(rhs.positionX_) - static_cast<long>(lhs.positionX_), 2) +
                  std::pow(static_cast<long>(rhs.positionY_) - static_cast<long>(lhs.positionY_), 2));

    return static_cast<size_t>(std::lround(distance));
}

Island::Island(size_t position_X, size_t position_Y)
    : position_(Coordinates(position_X, position_Y)) {}
