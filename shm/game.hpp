#pragma once

#include "map.hpp"
#include "player.hpp"

#include <cstddef>  // for size_t
#include <memory>

class Game {
public:
    enum class action {
        buy = 1,
        sell = 2,
        travel = 3,
        printCargo = 4,
    };

    Game(size_t money, size_t days, size_t finalGoal);
    ~Game() = default;
    void startGame();

private:
    size_t money_{};
    size_t days_{};
    size_t finalGoal_{};
    size_t currentDay_{};
    std::shared_ptr<Map> map_{};
    std::shared_ptr<Player> player_{};

    void printMenu();
};
