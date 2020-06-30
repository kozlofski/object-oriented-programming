#pragma once

#include <memory>

#include "cargo.hpp"
#include "player.hpp"

enum class Response { done,
                      lack_of_money,
                      lack_of_cargo,
                      lack_of_space };

class Store {
public:
    Store();
    void generate();
    void display();  // for testing - should be replaced by a friend operator <<

    Response buy(Cargo* cargo, size_t amount, Player* player);
    Response sell(Cargo* cargo, size_t amount, Player* player);

    void fillShop();

private:
    size_t capacity_{1000};
    std::vector<std::shared_ptr<Cargo>> goods_{};
};