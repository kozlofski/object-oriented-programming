#include "gtest/gtest.h"

#include "../player.hpp"
#include "../ship.hpp"
#include "../shm_time.hpp"

#include <memory>

constexpr int testMoney = 100;

TEST(playerTest, ConstructorAndGettersTest)
{
    Time t;
    auto shipTest = std::make_shared<Ship>(&t);
    Player playerTest{shipTest, testMoney};

    //TODO: How to test ship in player
    ASSERT_EQ(playerTest.getMoney(), testMoney);
    ASSERT_EQ(playerTest.getAvailableSpace(), 0);
}
