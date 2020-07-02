#pragma once

#include <cstddef>  // for size_t

class Game {
public:
    Game(size_t money, size_t days, size_t finalGoal);
    void startGame();

private:
    size_t money_{};
    size_t days_{};
    size_t finalGoal_{};
    size_t currentDay_{};
};
