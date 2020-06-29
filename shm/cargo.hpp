#pragma once

#include <string>

class Cargo {
public:
    Cargo(std::string name, size_t amount, size_t price);

    Cargo& operator+=(size_t amount);
    Cargo& operator-=(size_t amount);
    bool operator==(const Cargo& rhs) const;

    virtual std::string getName() const = 0;
    virtual size_t getAmount() const = 0;
    virtual size_t getBasePrice() const = 0;
    virtual size_t getPrice() const = 0;

private:
    std::string name_{};
    size_t amount_{};
    size_t basePrice_{};
};
