#include <gtest/gtest.h>
#include "math_utils.h"

TEST(UTILS, GCD) {
    EXPECT_EQ(5, euclidean_algorithm(5,10));
    EXPECT_EQ(7, euclidean_algorithm(21,49));
    EXPECT_EQ(1, euclidean_algorithm(17,13));
}

TEST(UTILS, LCM) {
    EXPECT_EQ(0, lcm(0,0)); // base case
    EXPECT_EQ(84, lcm(21,4)); // 7 * 3 * 4
    EXPECT_EQ(420, lcm(35,12)); // 3 * 4 * 5 * 7
}

TEST(UTILS, EULER_TOTIENT) {
    // N    1 	2 	3 	4 	5 	6 	7 	8 	9 	10 	11 	12 	13 	14 	15 	16 	17 	18 	19 	20 	21 	22 	23 	24 	25 	26 	27 	28 	29 	30 	31 	32 	33 	34 	35 	36
    // φ(n) 1 	1 	2 	2 	4 	2 	6 	4 	6 	4 	10 	4 	12 	6 	8 	8 	16 	6 	18 	8 	12 	10 	22 	8 	20 	12 	18 	12 	28 	8 	30 	16 	20 	16 	24 	12
    EXPECT_EQ(1, euler_totient(1));
    EXPECT_EQ(1, euler_totient(2));
    EXPECT_EQ(4, euler_totient(8));
    EXPECT_EQ(18, euler_totient(19)); // prime: n-1
    EXPECT_EQ(30, euler_totient(31)); // prime: n-1
    EXPECT_EQ(24, euler_totient(35));
    EXPECT_EQ(12, euler_totient(36));

}

TEST(UTILS, CARMICHAEL_TOTIENT) {
    // N        1 	2 	3 	4 	5 	6 	7 	8 	9 	10 	11 	12 	13 	14 	15 	16 	17 	18 	19 	20 	21 	22 	23 	24 	25 	26 	27 	28 	29 	30 	31 	32 	33 	34 	35 	36
    //  λ(n) 	1 	1 	2 	2 	4 	2 	6 	2 	6 	4 	10 	2 	12 	6 	4 	4 	16 	6 	18 	4 	6 	10 	22 	2 	20 	12 	18 	6 	28 	4 	30 	8 	10 	16 	12 	6
    EXPECT_EQ(1, carmichael_totient(1)); // base case
    EXPECT_EQ(1, carmichael_totient(2)); // prime
    EXPECT_EQ(2, carmichael_totient(8));
    EXPECT_EQ(18, carmichael_totient(19)); // prime: n-1
    EXPECT_EQ(30, carmichael_totient(31)); // prime: n-1
    EXPECT_EQ(12, carmichael_totient(35));
    EXPECT_EQ(6, carmichael_totient(36));
}
