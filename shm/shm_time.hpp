#pragma once

#include <vector>

#include "observer.hpp"

class Time {
public:
    Time() = default;

    void AddObserver(Observer* observer);
    void RemoveObserver(Observer* observer);
    Time& operator++();

private:
    std::vector<Observer*> observers_;
};
