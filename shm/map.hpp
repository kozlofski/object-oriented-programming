#pragma once

#include <vector>

#include "island.hpp"

constexpr size_t totalIslands = 10;
constexpr size_t mapWidth = 100;
constexpr size_t mapHeight = 100;

class Map {
public:
    Map();
    Island* getIsland(const Island::Coordinates& coordinates);
    Island* getCurrentPosition() const { return currentPosition_; };

private:
    Island* currentPosition_{};
    std::vector<Island> islands_{};

    void generateIsland(size_t howMany);
};
