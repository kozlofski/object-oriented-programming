#include "game.hpp"

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <string>

Game::Game(size_t money, size_t days, size_t finalGoal)
    : money_(money), days_(days), finalGoal_(finalGoal) {}

void Game::startGame()
{
    time_ = std::make_shared<Time>();
    player_ = std::make_shared<Player>(money_, time_.get());
    map_ = std::make_shared<Map>(time_.get());

    currentDay_ = time_->getElapsedTime();

    //Hire crew
    *player_->getShip() += player_->getShip()->getMaxCrew();

    std::system("clear");
    std::cout << "Welcome in SHM game, you have " << days_ << " days to earn "
              << finalGoal_ << ".\nGOOD LUCK!\n\n";

    while (true) {
        action actionChosen = chooseOption();

        if (actionChosen == action::quitGame) {
            std::cout << "\nQuit Game!\n\n";
            break;
        }
        makeAction(actionChosen);
    }

    if (checkWinConditions()) {
        printWinScreen();
    }
    else {
        printLooseScreen();
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
              << " Crew: " << player_->getShip()->getCrew()
              << "\nCurrent position: "
              << map_->getCurrentPosition()->getPosition()
              << '\n';
    printLine('*');
}

void Game::printOptions() const
{
    std::cout << "\nChoose number with action you wanna make\n\n";
    std::cout << "1. Buy\n2. Sell\n3. Tavel\n4. Print cargo on ship\n5. Quit game\n\n";
    std::cout << "Your choice: ";
}

Game::action Game::chooseOption() const
{
    size_t actionInput = std::numeric_limits<size_t>::max();
    do {
        resetScreen();
        printOptions();
        while (!(std::cin >> actionInput)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            resetScreen("You've chosen wrong number. Do it once again!\n");
            printOptions();
        }

        if (!checkOptions(actionInput)) {
            resetScreen("You've chosen wrong number. Do it once again!\n");
            printOptions();
        }
    } while (!checkOptions(actionInput));

    return static_cast<action>(actionInput);
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
    resetScreen("TRAVEL");
    auto islandToTravel = chooseIslandToTravel();
    auto travelTime = countTravelTime(islandToTravel);
    increseDays(travelTime);
    map_->travel(islandToTravel);
}

Island* Game::chooseIslandToTravel() const
{
    size_t inputX = std::numeric_limits<size_t>::max();
    size_t inputY = std::numeric_limits<size_t>::max();
    Island* chosenIsland = nullptr;

    do {
        std::cout << "Choose the island you want to go to:\n\n";
        std::cout << *map_;
        std::cout << "Your choice -> X Y: ";
        while (!(std::cin >> inputX >> inputY)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            resetScreen("You've chosen wrong Island. Do it once again!");

            std::cout << "Choose the island you want to go to. [X Y]\n\n";
            std::cout << *map_;
            std::cout << "Your choice: ";
        }
        chosenIsland = map_->getIsland(Island::Coordinates(inputX, inputY));

        if (!chosenIsland) {
            resetScreen("You've chosen wrong Island. Do it once again!");
        }
    } while (!chosenIsland);

    return chosenIsland;
}

size_t Game::countTravelTime(const Island* islandToTravel)
{
    auto travelDistance = map_->getDistanceToIsland(islandToTravel);
    return static_cast<size_t>(std::ceil(static_cast<double>(travelDistance) / static_cast<double>(player_->getSpeed())));
}

void Game::increseDays(const size_t days)
{
    auto daysNo = days;

    if (days > (days_ - currentDay_)) {
        daysNo = days_ - currentDay_;
    }

    while (daysNo--) {
        ++(*time_);
    }
    currentDay_ = time_->getElapsedTime();
}

void Game::buy()
{
    do {
        resetScreen("BUY");

        auto store = map_->getCurrentPosition()->getStore();
        Cargo* chosenCargo = chooseCargoToBuy(store);

        if (!chosenCargo) {
            return;
        }

        size_t amount = 0;
        std::cout << "How many cargo do you wanna buy?\n";
        while (!(std::cin >> amount)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            resetScreen("You've chosen wrong amount. Do it once again!\n");
        }

        std::cout << "You need to pay " << store->getCargoBuyPrice(chosenCargo, amount) << "$\n[yes/no]: ";
        std::string choice = "no";
        while (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (choice != "yes") {
            return;
        }

        auto response = store->buy(chosenCargo, amount, player_.get());
        switch (response) {
        case Store::Response::done:
            std::cout << "You've just bought " << amount << " of " << chosenCargo->getName() << '\n';
            break;
        case Store::Response::lack_of_cargo:
            std::cout << "Not enough cargo to buy!\n";
            break;
        case Store::Response::lack_of_money:
            std::cout << "You do not have enough money!\n";
            break;
        case Store::Response::lack_of_space:
            std::cout << "You do not have enough space for the cargo!\n";
            break;
        default:
            break;
        }
    } while (chooseCloseWindow());
}

Cargo* Game::chooseCargoToBuy(std::shared_ptr<Store> store) const
{
    size_t cargoPosition = 0;
    Cargo* chosenCargo = nullptr;

    do {
        std::cout << "Choose cargo you want to buy:\n\n";
        //TODO: change to operator<<
        store->listCargo();
        std::cout << "\n0     Cancel\n";

        std::cout << "Your choice: ";
        while (!(std::cin >> cargoPosition)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            resetScreen("You've chosen wrong cargo. Do it once again!");

            std::cout << "Choose cargo you want to buy:\n\n";
            store->listCargo();
            std::cout << "Your choice: ";
        }

        if (cargoPosition == 0) {
            return nullptr;
        }

        chosenCargo = store->getCargo(--cargoPosition);

        if (!chosenCargo) {
            resetScreen("You've chosen wrong cargo. Do it once again!");
        }
    } while (!chosenCargo);

    return chosenCargo;
}

void Game::sell()
{
    do {
        resetScreen("SELL");
        Cargo* chosenCargo = chooseCargoToSell();

        if (!chosenCargo) {
            return;
        }

        size_t amount = 0;
        std::cout << "How many cargo do you wanna sell?\n";
        while (!(std::cin >> amount)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            resetScreen("You've chosen wrong amount. Do it once again!\n");
        }

        auto cargoName = chosenCargo->getName();
        auto store = map_->getCurrentPosition()->getStore();
        std::cout << "You're gonna sell " << amount << " of " << cargoName << " for "
                  << store->getCargoSellPrice(chosenCargo, amount) << "$\n[yes/no]: ";
        std::string choice = "no";
        while (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (choice != "yes") {
            return;
        }

        auto response = store->sell(chosenCargo, amount, player_.get());
        switch (response) {
        case Store::Response::done:
            std::cout << "You've just sold " << amount << " of " << cargoName << '\n';
            break;
        case Store::Response::lack_of_cargo:
            std::cout << "Not enough cargo to sell!\n";
            break;
        default:
            break;
        }

    } while (chooseCloseWindow());
}

Cargo* Game::chooseCargoToSell() const
{
    size_t cargoPosition = 0;
    Cargo* chosenCargo = nullptr;

    do {
        sellPrintCargos();
        std::cout << "Choose cargo you want to sell:\n\n";

        std::cout << "Your choice: ";
        while (!(std::cin >> cargoPosition)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            resetScreen("You've chosen wrong cargo. Do it once again!");

            std::cout << "Choose cargo you want to buy:\n\n";
            sellPrintCargos();
            std::cout << "Your choice: ";
        }

        if (cargoPosition == 0) {
            return nullptr;
        }

        chosenCargo = player_->getShip()->getCargo(--cargoPosition);

        if (!chosenCargo) {
            resetScreen("You've chosen wrong cargo. Do it once again!");
        }
    } while (!chosenCargo);

    return chosenCargo;
}

void Game::sellPrintCargos() const
{
    printLine('~');
    std::cout << "CARGO ON SHIP\n";
    printLine('~');
    player_->printCargo();
    auto store = map_->getCurrentPosition()->getStore();
    std::cout << '\n';
    printLine('~');
    std::cout << "CARGO IN STORE\n";
    printLine('~');
    store->listCargo();
    std::cout << "\n0     Cancel\n";
}

void Game::printCargo()
{
    do {
        resetScreen("CARGO ON SHIP");
        player_->printCargo();
    } while (chooseCloseWindow());
}

void Game::resetScreen() const
{
    std::system("clear");
    printMenu();
}

void Game::resetScreen(const std::string& additionalInfo) const
{
    std::system("clear");
    printMenu();
    printLine('_');
    std::cout << "INFO: " << additionalInfo << '\n';
    printLine('_');
    std::cout << '\n';
}

void Game::printLine(char character) const
{
    std::string line(80, character);
    std::cout << line << '\n';
}

bool Game::chooseCloseWindow() const
{
    std::cout << "\nClose window? [yes/no]: ";
    std::string choice = "no";
    while (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return (choice != "yes");
}
