#include "ship.hpp"

#include <algorithm>
#include <iostream>

Ship::Ship(int maxCrew, int speed, size_t id, const std::string& name, int capacity, Delegate* delegate, Time* timeObserver)
    : maxCrew_(maxCrew),
      speed_(speed),
      id_(id),
      name_(name),
      capacity_(capacity),
      delegatePlayer_(delegate),
      timeObserver_(timeObserver),
      crew_(0)
{
    if (timeObserver_) {
        timeObserver_->addObserver(this);
    }
}

Ship::Ship(int maxCrew, int speed, size_t id, Time* timeObserver)
    : Ship(maxCrew, speed, id, "", 0, nullptr, timeObserver) {}

Ship::Ship(Time* timeObserver)
    : Ship(0, 0, 0, "", 0, nullptr, timeObserver) {}

Ship::~Ship()
{
    if (timeObserver_) {
        timeObserver_->removeObserver(this);
    }
}

void Ship::setName(const std::string& name)
{
    name_ = name;
}

Ship& Ship::operator+=(const size_t crew)
{
    if (crew_ + crew > maxCrew_) {
        std::cerr << "Max crew exceeded\n";
        return *this;
    }
    crew_ += crew;
    return *this;
}

Ship& Ship::operator-=(const size_t crew)
{
    if (crew_ < crew) {
        std::cerr << "Crew number can't be negative\n";
        return *this;
    }
    crew_ -= crew;
    return *this;
}

void Ship::unload(Cargo* cargo)
{
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

void Ship::load(std::shared_ptr<Cargo> cargo)
{
    for (const auto& el : cargo_) {
        if (*el == *cargo) {
            *el += cargo->getAmount();
            return;
        }
    }
    cargo_.emplace_back(cargo);
}

void Ship::printCargo() const
{
    for (const auto& el : cargo_) {
        el->print();
        std::cout << '\n';
    }
}

void Ship::nextDay()
{
    // std::cout << "Ship nextDay\n";
    if (delegatePlayer_) {
        delegatePlayer_->PayCrew(crew_);
    }
}
