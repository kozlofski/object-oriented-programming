#pragma once

#include <memory>

#include "cargo.hpp"
#include "player.hpp"
#include "shm_time.hpp"

class Store : public Time::IObserver {
public:
    enum class Response { done,
                          lack_of_money,
                          lack_of_cargo,
                          lack_of_space,
    };

    Store(Time* timeObserver);

    //Override from Time::IObserver
    ~Store() override;
    void nextDay() override;

    Cargo* getCargo(const size_t pos);

    Store::Response buy(Cargo* cargo, size_t amount, Player* player);
    Store::Response sell(Cargo* cargo, size_t amount, Player* player);

    void listCargo();

private:
    Time* timeObserver_{};
    std::vector<std::shared_ptr<Cargo>> assortment_{};

    const size_t maxCargo_{10};
    const size_t maxAmount_{25};

    Cargo* findMatchCargo(Cargo* cargo);
    void removeFromStore(Cargo* cargo);
    void generateCargo();
};
