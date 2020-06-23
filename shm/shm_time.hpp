#pragma once

#include <vector>

class Time {
public:
    class Observer {
    public:
        virtual ~Observer() = default;
        virtual void NextDay() = 0;
    };

    Time() = default;

    size_t getElapsedTime() const { return elapsedTime_; }

    void AddObserver(Observer* observer);
    void RemoveObserver(Observer* observer);
    Time& operator++();

private:
    size_t elapsedTime_{0};
    std::vector<Observer*> observers_;
};
