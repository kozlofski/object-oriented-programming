#include "game.hpp"

#include <iostream>
#include <string>

const std::string line(80, '*');
constexpr int shipMaxCrew = 50;
constexpr int shipSpeed = 10;
constexpr size_t shipId = 7;
const std::string& shipName = "Black Perl";
constexpr int shipCapacity = 250;

Game::Game(size_t money, size_t days, size_t finalGoal)
    : money_(money), days_(days), finalGoal_(finalGoal), currentDay_(0) {}

void Game::startGame() {
    auto gameShip = std::make_shared<Ship>(shipMaxCrew, shipSpeed, shipId, shipName, shipCapacity);
    player_ = std::make_shared<Player>(gameShip, money_, 0);
    map_ = std::make_shared<Map>();
    std::cout << "Welcome in SHM game, you have " << days_ << " days to earn "
              << finalGoal_ << ".\nGOOD LUCK!\n\n";
    printMenu();
}

void Game::printMenu() {
    std::cout << line << "\n\n";
    //TODO: print data from Time class!!!
    std::cout << "Money: " << player_->getMoney()
              << " Day: 1"
              << " Days left: 99"
              << "\nCurrent position: "
              << map_->getCurrentPosition()->getPosition()
              << "\n\n";
}
