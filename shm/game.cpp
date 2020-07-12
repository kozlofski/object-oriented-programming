#include "game.hpp"

#include <iostream>
#include <memory>
#include <string>

const std::string line(80, '*');

Game::Game(size_t money, size_t days, size_t finalGoal)
    : money_(money), days_(days), finalGoal_(finalGoal), currentDay_(1) {}

void Game::startGame()
{
    time_ = std::make_shared<Time>();
    player_ = std::make_shared<Player>(money_, time_.get());
    map_ = std::make_shared<Map>(time_.get());

    std::cout << "Welcome in SHM game, you have " << days_ << " days to earn "
              << finalGoal_ << ".\nGOOD LUCK!\n\n";
    printMenu();
}

void Game::printMenu()
{
    std::cout << line << "\n\n";
    //TODO: print data from Time class!!!
    std::cout << "Money: " << player_->getMoney()
              << " Day: " << currentDay_
              << " Days left: " << days_ - currentDay_
              << "\nCurrent position: "
              << map_->getCurrentPosition()->getPosition()
              << "\n\n";

    map_->getCurrentPosition()->getStore()->listCargo();

    std::cout << "\n"
              << *map_ << '\n';
}
