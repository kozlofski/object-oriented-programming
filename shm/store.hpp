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

    Cargo* getCargo(const size_t pos) const;
    size_t getCargoBuyPrice(Cargo* cargoInStore, size_t amount) const;
    size_t getCargoSellPrice(Cargo* cargoInStore, size_t amount) const;

    Store::Response buy(Cargo* cargoInStore, size_t amount, Player* player);
    Store::Response sell(Cargo* cargo, size_t amount, Player* player);

    void listCargo();

private:
    Time* timeObserver_{};
    std::vector<std::shared_ptr<Cargo>> assortment_{};

    const size_t maxCargo_{10};
    const size_t maxAmount_{25};

    Cargo* findMatchCargo(Cargo* cargo) const;
    void generateCargo();
    std::shared_ptr<Cargo> createCargo(Cargo* cargo, size_t amount);
};
