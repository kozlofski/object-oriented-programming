#include "gtest/gtest.h"

#include "../player.hpp"
#include "../ship.hpp"
#include "../shm_time.hpp"

#include <memory>

constexpr int testMoney = 100;
constexpr size_t testAvailableSpace = 200;

TEST(playerTest, ConstructorAndGettersTest)
{
    Time t;
    Ship shipTest(&t);
    Player playerTest(shipTest, testMoney, testAvailableSpace);

    //TODO: How to test ship in player
    ASSERT_EQ(playerTest.getMoney(), testMoney);
    ASSERT_EQ(playerTest.getAvailableSpace(), testAvailableSpace);
}
