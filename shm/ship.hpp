#pragma once

#include <memory>
#include <string>
#include <vector>

#include "cargo.hpp"
#include "shm_time.hpp"

class Ship : public Time::IObserver {
public:
    class Delegate {
    public:
        virtual ~Delegate() = default;
        virtual void PayCrew(size_t money) = 0;
    };

    Ship(Time* timeObserver);
    Ship(int maxCrew, int speed, size_t id, const std::string& name, int capacity, Delegate* delegate, Time* timeObserver);
    Ship(int maxCrew, int speed, size_t id, Time* timeObserver);

    // Override from Time::IObserver
    ~Ship() override;

    void setName(const std::string& name);
    Ship& operator+=(const size_t crew);
    Ship& operator-=(const size_t crew);

    size_t getCapacity() const { return capacity_; }
    size_t getMaxCrew() const { return maxCrew_; }
    size_t getSpeed() const { return speed_; }
    std::string getName() const { return name_; }
    size_t getId() const { return id_; }
    size_t getCrew() const { return crew_; }
    Cargo* getCargo(size_t index) { return cargo_[index].get(); }
    std::vector<std::shared_ptr<Cargo>> getCargos() const { return cargo_; }

    void load(std::shared_ptr<Cargo> cargo);
    void unload(Cargo* cargo);
    void printCargo() const;

    // Override from Time::IObserver
    void nextDay() override;

private:
    size_t maxCrew_{};
    size_t speed_{};
    const size_t id_{};
    std::string name_{};
    size_t capacity_{};
    Delegate* delegatePlayer_{};
    Time* timeObserver_{};

    size_t crew_{};
    std::vector<std::shared_ptr<Cargo>> cargo_{};
};
