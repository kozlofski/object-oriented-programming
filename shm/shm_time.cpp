#include "shm_time.hpp"

#include <algorithm>
#include <iostream>

void Time::AddObserver(IObserver* observer) {
    if (std::find(std::begin(observers_),
                  std::end(observers_),
                  observer) == std::end(observers_)) {
        observers_.push_back(observer);
    }
    std::cout << "AddObserver " << observers_.size() << '\n';
}

void Time::RemoveObserver(IObserver* observer) {
    observers_.erase(std::remove(std::begin(observers_),
                                 std::end(observers_),
                                 observer),
                     std::end(observers_));
    std::cout << "RemoveObserver " << observers_.size() << '\n';
}

Time& Time::operator++() {
    elapsedTime_++;
    std::cout << "operator " << observers_.size() << ' ' << getElapsedTime() << '\n';
    for (const auto& observer : observers_) {
        observer->NextDay();
    }
    return *this;
}
