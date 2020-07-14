#include "game.hpp"

int main()
{
    constexpr size_t kMoney = 1000;
    constexpr size_t kDays = 10;
    constexpr size_t kFinalGoal = 5000;

    Game game(kMoney, kDays, kFinalGoal);
    game.startGame();

    return 0;
}
