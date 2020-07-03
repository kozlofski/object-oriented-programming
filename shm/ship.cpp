#include "ship.hpp"

#include <algorithm>
#include <iostream>

Ship::Ship()
    : id_(0) {}

Ship::Ship(int maxCrew, int speed, size_t id, const std::string& name, int capacity)
    : maxCrew_(maxCrew), speed_(speed), id_(id), name_(name), capacity_(capacity), crew_(0) {}

Ship::Ship(int maxCrew, int speed, size_t id)
    : Ship(maxCrew, speed, id, "", 0) {}

void Ship::setName(const std::string& name) {
    name_ = name;
}

Ship& Ship::operator+=(const size_t crew) {
    if (crew_ + crew > maxCrew_) {
        std::cerr << "Max crew exceeded\n";
        return *this;
    }
    crew_ += crew;
    return *this;
}

Ship& Ship::operator-=(const size_t crew) {
    if (crew_ < crew) {
        std::cerr << "Crew number can't be negative\n";
        return *this;
    }
    crew_ -= crew;
    return *this;
}

void Ship::unload(Cargo* cargo) {
    auto it = std::find_if(cargo_.begin(), cargo_.end(), [cargo](const std::shared_ptr<Cargo> ptr) {
        return *ptr == *cargo;
    });
    if (it == cargo_.end()) {
        std::cerr << "yerr we couldnt find this cargo comrade!\n";
        return;
    }
    if ((*it)->getAmount() < cargo->getAmount()) {
        std::cerr << "cargo would be negative\n";
        return;
    }
    *(*it) -= (cargo->getAmount());
    if ((*it)->getAmount() == 0) {
        cargo_.erase(it);
        cargo_.shrink_to_fit();
    }
}

void Ship::load(std::shared_ptr<Cargo> cargo) {
    for (const auto& el : cargo_) {
        if (el == cargo) {
            *el += cargo->getAmount();
            return;
        }
    }
    std::find_if(cargo_.begin(), cargo_.end(), [cargo](const auto& el) {
        return el == cargo;
    });
    cargo_.emplace_back(cargo);
}

void Ship::load(std::shared_ptr<Cargo> cargo) {
    for (const auto& el : cargo_) {
        if (el->getName() == cargo->getName()) {
            *el += cargo->getAmount();
            return;
        }
    }
    cargo_.emplace_back(cargo);
}

void Ship::load(std::shared_ptr<Cargo> cargo) {
    for (const auto& el : cargo_) {
        if (el->getName() == cargo->getName()) {
            *el += cargo->getAmount();
            return;
        }
    }
    cargo_.emplace_back(cargo);
}
