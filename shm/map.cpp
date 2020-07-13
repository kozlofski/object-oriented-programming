#include "map.hpp"

#include <algorithm>
#include <iomanip>
#include <random>
#include <vector>

Map::Map(Time* timeObserver)
{
    islands_.reserve(totalIslands);
    generateIsland(totalIslands, timeObserver);
    currentPosition_ = &islands_.front();
}

void Map::generateIsland(size_t howMany, Time* timeObserver)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> xDistrib(0, mapWidth);
    std::uniform_int_distribution<> yDistrib(0, mapHeight);

    for (size_t i = 0; i < howMany; i++) {
        int newX;
        int newY;
        do {
            newX = xDistrib(gen);
            newY = yDistrib(gen);
        } while (std::any_of(islands_.begin(), islands_.end(), [=](auto island) {
            return island.getPosition() == Island::Coordinates(newX, newY);
        }));
        islands_.emplace_back(newX, newY, timeObserver);
    }
}

Island* Map::getIsland(const Island::Coordinates& coordinates)
{
    auto foundIsland = std::find_if(std::begin(islands_),
                                    std::end(islands_),
                                    [&coordinates](const auto& island) {
                                        return island.getPosition() == coordinates;
                                    });
    if (foundIsland != std::end(islands_)) {
        return &*foundIsland;
    }
    return nullptr;
}

size_t Map::getDistanceToIsland(const Island* destination) const
{
    return Island::Coordinates::distance(getCurrentPosition()->getPosition(), destination->getPosition());
}

void Map::travel(Island* destination)
{
    currentPosition_ = destination;
}

std::ostream&
operator<<(std::ostream& output, const Map& map)
{
    size_t i = 1;
    for (const auto& island : map.islands_) {
        auto distanceToIsland = map.getDistanceToIsland(&island);
        std::cout << std::setw(2) << i++ << ". " << island.getPosition()
                  << " ---> Distance: " << distanceToIsland;
        if (distanceToIsland == 0) {
            std::cout << "   --------> You are here";
        }
        std::cout << '\n';
    }
    return output;
}
