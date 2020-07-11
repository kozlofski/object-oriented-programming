#pragma once

#include <vector>

class Time {
public:
    class IObserver {
    public:
        virtual ~IObserver() = default;
        virtual void nextDay() = 0;
    };

    Time() = default;

    size_t getElapsedTime() const { return elapsedTime_; }

    void addObserver(IObserver* observer);
    void removeObserver(IObserver* observer);
    Time& operator++();

private:
    size_t elapsedTime_{};
    std::vector<IObserver*> observers_{};
};
