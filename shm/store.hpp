#pragma once

#include <memory>

#include "cargo.hpp"
#include "player.hpp"
// #include #time.hpp"

class Store {
public:
    enum class Response { done,
                          lack_of_money,
                          lack_of_cargo,
                          lack_of_space,
    };

    // Store(Time* time);
    Store();
    ~Store();
    void nextDay();
    Cargo* getCargo(const size_t pos);
    void generateCargo();
    Store::Response buy(Cargo* cargo, size_t amount, Player* player);  //private?
    Store::Response sell(Cargo* cargo, size_t amount, Player* player);

    void listCargo();

    friend std::ostream& operator<<(std::ostream& out, const Store& store);

private:
    std::vector<std::shared_ptr<Cargo>> assortment_{};
    const size_t maxCargo_ = 10;
    const size_t maxAmount = 25;

    Cargo* findMatchCargo(Cargo* cargo);
    void removeFromStore(Cargo* cargo);
};