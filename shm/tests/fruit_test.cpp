#include "gtest/gtest.h"

#include "../fruit.hpp"
#include "../shm_time.hpp"

#include <string>

const std::string testName = "Sword Of Destiny";
constexpr size_t testAmount = 200;
constexpr size_t testBasePrice = 40;
constexpr size_t testTimeToExpire = 8;

TEST(fruitTest, ConstructorAndGettersTest) {
    Time t;
    Fruit fruitTest(testName, testAmount, testBasePrice, &t, testTimeToExpire);

    ASSERT_EQ(fruitTest.getName(), testName);
    ASSERT_EQ(fruitTest.getAmount(), testAmount);
    ASSERT_TRUE(fruitTest.getPrice() < testBasePrice);
}
