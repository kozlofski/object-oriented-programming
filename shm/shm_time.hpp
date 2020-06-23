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

    void AddObserver(Observer* observer);
    void RemoveObserver(Observer* observer);
    Time& operator++();

private:
    std::vector<Observer*> observers_;
};
