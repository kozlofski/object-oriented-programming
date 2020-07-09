

#include "alcohol.hpp"
#include "cargo.hpp"
#include "fruit.hpp"
#include "item.hpp"
#include "shm_time.hpp"
#include "store.hpp"

int main()
{
    Time t;

    Fruit f{"Apple", 100, 20, &t, 100};
    Alcohol a{"Vodka", 500, 50, &t, 48};
    Item i{"Sword", 50, 800, &t, Item::Rarity::legendary};

    Store st{&t};
    st.listCargo();

    ++t;
    st.listCargo();
    ++t;
    st.listCargo();

    return 0;
}
