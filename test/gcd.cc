#include <gtest/gtest.h>
#include "math.hpp"
#include <iostream>

TEST(UTILS, GCD) {
    EXPECT_EQ(5, euclidean_algorithm(5,10));
}