#pragma once

#include "cargo.hpp"
#include "player.hpp"

enum class Response { done,
                      lack_of_money,
                      lack_of_cargo,
                      lack_of_space };

Response buy(Cargo* cargo, size_t amount, Player* player);
Response sell(Cargo* cargo, size_t amount, Player* player);

class Store {
Store();

public:
private:
    size_t capacity_{100};
};