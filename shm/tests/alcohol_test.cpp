#include "gtest/gtest.h"

#include "../alcohol.hpp"
#include "../shm_time.hpp"

#include <string>

const std::string testName = "Spirytus";
constexpr size_t testAmount = 200;
constexpr size_t testBasePrice = 40;
constexpr size_t testAlcoholPower = 94;

TEST(alcoholTest, ConstructorAndGettersTest)
{
    Time t;
    Alcohol alcoholTest(testName, testAmount, testBasePrice, &t, testAlcoholPower);

    ASSERT_EQ(alcoholTest.getName(), testName);
    ASSERT_EQ(alcoholTest.getAmount(), testAmount);
    ASSERT_TRUE(alcoholTest.getPrice() < testBasePrice);
}
