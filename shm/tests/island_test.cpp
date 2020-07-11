#include <tuple>
#include "gtest/gtest.h"

#include "../island.hpp"

constexpr size_t testPositionX = 100;
constexpr size_t testPositionY = 200;

TEST(islandTest, ConstructorAndGettersTest)
{
    Island islandTest(testPositionX, testPositionY);
    Island::Coordinates testCoordinates(testPositionX, testPositionY);

    auto coordinates = islandTest.getPosition();

    ASSERT_TRUE(coordinates == testCoordinates);
}

class IslandDistanceFixture : public ::testing::TestWithParam<std::tuple<size_t, size_t, size_t, size_t, size_t>> {
};

TEST_P(IslandDistanceFixture, CheckDistance)
{
    Island::Coordinates lhs(std::get<0>(GetParam()), std::get<1>(GetParam()));
    Island::Coordinates rhs(std::get<2>(GetParam()), std::get<3>(GetParam()));

    EXPECT_EQ(Island::Coordinates::distance(lhs, rhs), std::get<4>(GetParam()));
    EXPECT_EQ(Island::Coordinates::distance(lhs, rhs), Island::Coordinates::distance(rhs, lhs));
}

INSTANTIATE_TEST_SUITE_P(
    IslandDistanceTests,
    IslandDistanceFixture,
    ::testing::Values(
        std::make_tuple(0, 0, 10, 10, 14),
        std::make_tuple(0, 0, 3, 4, 5),
        std::make_tuple(10, 10, 7, 6, 5),
        std::make_tuple(12, 0, 0, 16, 20),
        std::make_tuple(155, 199, 27, 66, 185),
        std::make_tuple(155, 0, 0, 66, 168)));
