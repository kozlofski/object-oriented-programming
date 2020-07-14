#pragma once

#include <vector>

#include "island.hpp"

constexpr size_t totalIslands = 10;
constexpr size_t mapWidth = 100;
constexpr size_t mapHeight = 100;

class Time;

class Map {
public:
    Map(Time* timeObserver);
    Island* getIsland(const Island::Coordinates& coordinates);
    Island* getCurrentPosition() const { return currentPosition_; };
    size_t getTotalIslans() const { return totalIslands; };

    size_t getDistanceToIsland(const Island* destination) const;
    void travel(Island* destination);
    friend std::ostream& operator<<(std::ostream& output, const Map& map);

private:
    Island* currentPosition_{};
    std::vector<Island> islands_{};

    void generateIsland(size_t howMany, Time* timeObserver);
};
