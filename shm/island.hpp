#pragma once

#include <cstddef>  // for size_t
#include <iostream>

class Island {
public:
    class Coordinates {
    public:
        Coordinates() = default;
        Coordinates(size_t positionX, size_t positionY);

        bool operator==(const Coordinates& rhs) const;

        static size_t distance(const Coordinates& lhs, const Coordinates& rhs);
        friend std::ostream& operator<<(std::ostream& output, const Coordinates& coordinates);

    private:
        size_t positionX_{};
        size_t positionY_{};
    };

    Island(size_t position_X, size_t position_Y);
    Coordinates getPosition() const { return position_; }

private:
    Coordinates position_{};
};
