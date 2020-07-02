#pragma once

#include <memory>

#include "cargo.hpp"
#include "player.hpp"

class Store {
public:
    enum class Response { done,
                          lack_of_money,
                          lack_of_cargo,
                          lack_of_space,
                          cancelled,
    };

    Store();
    void generate();
    void purchase(Player* player);
    void sale(Player* player);
    size_t listCargo(std::vector<std::shared_ptr<Cargo>> cargos);

private:
    Store::Response buy(Cargo* cargo, size_t amount, Player* player);  //private?
    Cargo* chooseCargoToBuy(size_t i);
    Store::Response sell(Cargo* cargo, size_t amount, Player* player);
    Cargo* chooseCargoToSell(std::vector<std::shared_ptr<Cargo>> cargoOnShip, size_t i);
    size_t capacity_{1000};                        // for future improvement
    std::vector<std::shared_ptr<Cargo>> goods_{};  // more descriptive name, like polish "asortyment"?
    const size_t maxCargo_ = 10;
};
