#pragma once

#include "island.hpp"
#include "map.hpp"
#include "player.hpp"
#include "shm_time.hpp"

#include <cstddef>  // for size_t
#include <memory>
#include <string>

class Game {
public:
    enum class action {
        buy = 1,
        sell = 2,
        travel = 3,
        printCargo = 4,
        quitGame = 5,
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
    std::shared_ptr<Time> time_{};

    bool checkWinConditions() const;
    bool checkLooseConditions() const;
    void printMenu() const;
    void printOptions() const;
    action chooseOption() const;
    bool checkOptions(size_t option) const;
    void printWinScreen();
    void printLooseScreen();
    void makeAction(action choice);
    void travel();
    Island* chooseIslandToTravel() const;
    size_t countTravelTime(const Island* islandToTravel);
    void increseDays(const size_t days);
    void buy();
    Cargo* chooseCargoToBuy(std::shared_ptr<Store> store) const;
    void sell();
    void printCargo();
    void resetScreen() const;
    void resetScreen(const std::string& additionalInfo) const;
    void printLine(char character) const;
    bool chooseCloseWindow() const;
};
