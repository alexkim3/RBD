#include <gtest/gtest.h>
#include "Pile.h"
#include "Container.h"
#include "Ball.h"


int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(CONTAINER, ctor)
{
    Container basket;
    ASSERT_TRUE(basket.m_radius == 20);
    ASSERT_TRUE(basket.m_position.m_x == 0.0f);
    ASSERT_TRUE(basket.m_position.m_y == 0.0f);
    ASSERT_TRUE(basket.m_position.m_z == 0.0f);

}

TEST(BALL, ctor)
{
    Ball pixar;
    ASSERT_TRUE(pixar.m_velocity.m_x == 0.0f);
    ASSERT_TRUE(pixar.m_velocity.m_y == 0.0f);
    ASSERT_TRUE(pixar.m_velocity.m_z == 0.0f);

    ASSERT_TRUE(pixar.m_radius == 2.0f);

    ASSERT_TRUE(pixar.m_position.m_x == 0.0f);
    ASSERT_TRUE(pixar.m_position.m_y == 0.0f);
    ASSERT_TRUE(pixar.m_position.m_z == 0.0f);

    ASSERT_TRUE(pixar.m_dampingXZ == 0.995f);

    ASSERT_TRUE(pixar.m_dampingY == 0.9f);

}

TEST(BALL, GetGravity)
{
    Ball pixar;
    ASSERT_TRUE(pixar.m_gravity == 0.005f);
    pixar.getGravity();
    ASSERT_EQ(pixar.getGravity(), 0.005f);
}


