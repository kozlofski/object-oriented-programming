#include "cargo.hpp"
#include "shm_time.hpp"

int main() {
    Time t;
    Cargo c1{"c1", 100, 40, &t};
    Cargo c2{"c2", 100, 40, &t};

    // t.AddObserver(&c1);
    // t.AddObserver(&c2);

    ++t;
    ++t;

    // t.RemoveObserver(&c2);
    // t.RemoveObserver(&c1);

    return 0;
}
