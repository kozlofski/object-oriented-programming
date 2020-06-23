#pragma once

#include <string>

#include "shm_time.hpp"

class Cargo : public Time::Observer {
public:
    Cargo(std::string name, size_t amount, size_t basePrice);

    Cargo& operator+=(size_t amount);
    Cargo& operator-=(size_t amount);
    ~Cargo() override = default;

    bool operator==(const Cargo& rhs) const;

    virtual std::string getName() const = 0;
    virtual size_t getAmount() const = 0;
    virtual size_t getBasePrice() const = 0;
    virtual size_t getPrice() const = 0;

    virtual void nextDay() = 0;

protected:
    std::string name_{};
    size_t amount_{};
    size_t basePrice_{};
    virtual bool equals(const Cargo& rhs) const = 0;
};
