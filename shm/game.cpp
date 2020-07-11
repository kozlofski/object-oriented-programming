#include "game.hpp"

#include "shm_time.hpp"

#include <iostream>
#include <memory>
#include <string>

const std::string line(80, '*');

Game::Game(size_t money, size_t days, size_t finalGoal)
    : money_(money), days_(days), finalGoal_(finalGoal), currentDay_(0) {}

void Game::startGame()
{
    auto time = std::make_shared<Time>();
    player_ = std::make_shared<Player>(money_, time.get());
    map_ = std::make_shared<Map>();

    std::cout << "Welcome in SHM game, you have " << days_ << " days to earn "
              << finalGoal_ << ".\nGOOD LUCK!\n\n";
    printMenu();
}

void Game::printMenu()
{
    std::cout << line << "\n\n";
    //TODO: print data from Time class!!!
    std::cout << "Money: " << player_->getMoney()
              << " Day: 1"
              << " Days left: 99"
              << "\nCurrent position: "
              << map_->getCurrentPosition()->getPosition()
              << "\n\n";
}
