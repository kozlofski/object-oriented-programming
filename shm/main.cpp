#include "cargo.hpp"
#include "shm_time.hpp"

int main() {
    Cargo c1{"c1", 100, 40};
    Cargo c2{"c2", 100, 40};

    Time t;

    t.AddObserver(&c1);
    t.AddObserver(&c2);

    ++t;
    ++t;

    t.RemoveObserver(&c2);
    t.RemoveObserver(&c1);

    return 0;
}
