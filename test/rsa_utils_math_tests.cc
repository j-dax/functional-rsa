#include <gtest/gtest.h>
#include "math_utils.h"

using namespace rsa_utils;

TEST(MATH_UTILS, GCD) {
    EXPECT_EQ(5, euclidean_algorithm(5,10));
    EXPECT_EQ(7, euclidean_algorithm(21,49));
    EXPECT_EQ(1, euclidean_algorithm(17,13));
}

TEST(MATH_UTILS, LCM) {
    EXPECT_EQ(0, lcm(0,0)); // base case
    EXPECT_EQ(84, lcm(21,4)); // 7 * 3 * 4
    EXPECT_EQ(420, lcm(35,12)); // 3 * 4 * 5 * 7
}