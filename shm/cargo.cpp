#include <string>
#include <iostream>

class Cargo
{
public:
    Cargo(std::string &name, size_t &amount, size_t &basePrice) 
    : name_(name), amount_(amount), basePrice_(basePrice)
    {}

    Cargo &operator+=(size_t amount)
    {
        amount_ += amount;
        return *this;
    }
    Cargo &operator-=(size_t amount)
    {
        amount_ -= amount;
        return *this;
    }

    bool operator==(const Cargo &rhs)
    {
        if (name_ == rhs.name_ && basePrice_ == rhs.basePrice_) {
            std::cout << "Towary sa takie same";
            return true;
        }
            std::cout << "Towary nie sa takie same";
            return false;
    }

    std::string getName() const { return name_; }
    size_t getAmount() const { return amount_; }
    size_t getbasePrice() const { return basePrice_; }

    
    ~Cargo();

protected:
    std::string name_;
    size_t amount_;
    size_t basePrice_;
};

int main()
{
    return 0;
}