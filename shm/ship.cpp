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
    if (cargo->getAmount() == 0) {
        cargo_.erase(std::find_if(std::begin(cargo_), std::end(cargo_),
                                  [cargo](const auto& el) {
                                      return *el == *cargo;
                                  }));
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
    size_t i{1};
    for (const auto& el : cargo_) {
        std::cout << i++;
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
