#include "game.hpp"

#include <iostream>
#include <limits>
#include <memory>
#include <string>

Game::Game(size_t money, size_t days, size_t finalGoal)
    : money_(money), days_(days), finalGoal_(finalGoal), currentDay_(1) {}

void Game::startGame()
{
    time_ = std::make_shared<Time>();
    player_ = std::make_shared<Player>(money_, time_.get());
    map_ = std::make_shared<Map>(time_.get());

    std::system("clear");
    std::cout << "Welcome in SHM game, you have " << days_ << " days to earn "
              << finalGoal_ << ".\nGOOD LUCK!\n\n";

    while (true) {
        size_t actionInput = std::numeric_limits<size_t>::max();
        do {
            clearScreen();
            printOptions();
            while (!(std::cin >> actionInput)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                clearScreen("You've chosen wrong number. Do it once again!\n");
                printOptions();
            }

            std::cout << '\n'
                      << actionInput << '\n';
            if (!checkOptions(actionInput)) {
                clearScreen("You've chosen wrong number. Do it once again!\n");
                printOptions();
            }
        } while (!checkOptions(actionInput));

        action actionChosen = static_cast<action>(actionInput);
        if (actionChosen == action::quitGame) {
            std::cout << "\nQuit Game!\n\n";
            if (checkWinConditions()) {
                printWinScreen();
            }
            else {
                printLooseScreen();
            }
            break;
        }
        makeAction(actionChosen);
        // std::system("clear");
    }
}

bool Game::checkWinConditions() const
{
    return player_->getMoney() >= finalGoal_;
}

bool Game::checkLooseConditions() const
{
    if (player_->getMoney() == 0) {
        return true;
    }
    if ((currentDay_ >= days_) && (player_->getMoney() < finalGoal_)) {
        return true;
    }
    return false;
}

void Game::printMenu() const
{
    printLine('*');
    std::cout << "Money: " << player_->getMoney()
              << " Day: " << currentDay_
              << " Days left: " << days_ - currentDay_
              << "\nCurrent position: "
              << map_->getCurrentPosition()->getPosition()
              << '\n';
    printLine('*');
    std::cout << '\n';
}

void Game::printOptions() const
{
    std::cout << "Choose number with action you wanna make\n\n";
    std::cout << "1. Buy\n2. Sell\n3. Tavel\n4. Print cargo on ship\n5. Quit game\n\n";
    std::cout << "Your choice: ";
}

bool Game::checkOptions(size_t option) const
{
    return ((option >= static_cast<size_t>(action::buy)) &&
            (option <= static_cast<size_t>(action::quitGame)));
}

void Game::printWinScreen()
{
    // std::system("clear");
    std::cout << "Win screen!!\n";
}

void Game::printLooseScreen()
{
    // std::system("clear");
    std::cout << "Loose screen!!\n";
}

void Game::makeAction(action choice)
{
    switch (choice) {
    case action::buy:
        buy();
        break;
    case action::sell:
        sell();
        break;
    case action::travel:
        travel();
        break;
    case action::printCargo:
        printCargo();
        break;
    default:
        break;
    }
}

void Game::travel()
{
    clearScreen("TRAVEL");
    auto islandToTravel = chooseIslandToTravel();
}

Island* Game::chooseIslandToTravel() const
{
    size_t inputX = std::numeric_limits<size_t>::max();
    size_t inputY = std::numeric_limits<size_t>::max();
    Island* chosenIsland = nullptr;

    do {
        std::cout << "Choose the island you want to go to:\n\n";
        std::cout << *map_;
        std::cout << "Your choice: ";
        while (!(std::cin >> inputX >> inputY)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            clearScreen("You've chosen wrong Island. Do it once again!");

            std::cout << "Choose the island you want to go to:\n\n";
            std::cout << *map_;
            std::cout << "Your choice: ";
        }
        chosenIsland = map_->getIsland(Island::Coordinates(inputX, inputY));

        if (!chosenIsland) {
            clearScreen("You've chosen wrong Island. Do it once again!");
        }
    } while (!chosenIsland);

    return chosenIsland;
}

void Game::buy()
{
}

void Game::sell()
{
}

void Game::printCargo()
{
}

void Game::clearScreen() const
{
    std::system("clear");
    printMenu();
}

void Game::clearScreen(std::string additionalInfo) const
{
    std::system("clear");
    printLine('_');
    std::cout << "INFO: " << additionalInfo << '\n';
    printLine('_');
    std::cout << '\n';
    printMenu();
}

void Game::printLine(char character) const
{
    std::string line(80, character);
    std::cout << line << '\n';
}
