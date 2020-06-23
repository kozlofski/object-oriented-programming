
#include "alcohol.hpp"

bool Alcohol::equals(const Cargo& rhs) const {
    const Alcohol* rAlcohol = dynamic_cast<const Alcohol*>(&rhs);
    if (!rAlcohol)
        return false;
    return (name_ == rAlcohol->name_ &&
            percentage_ == rAlcohol->percentage_);
}
