#include <gtest/gtest.h>
#include "large_number.h"

using namespace rsa;

TEST(LARGE_NUMBER_ASSUMPTION, INSTANTIATION_DOES_NOT_THROW) {
    // LargeNumber();
    // LargeNumber::LargeNumber(uint8_t);
    // LargeNumber(const std::vector<uint8_t>);
    // LargeNumber(LargeNumber&);
    EXPECT_NO_THROW(LargeNumber());
    EXPECT_NO_THROW(LargeNumber(0));
    EXPECT_NO_THROW(LargeNumber(UINT8_MAX));
    EXPECT_NO_THROW(LargeNumber({UINT8_MAX,UINT8_MAX,UINT8_MAX,UINT8_MAX}));
    EXPECT_NO_THROW(LargeNumber({0,1,2,3,4})); // 0x 04 03 02 01 00
    EXPECT_NO_THROW(LargeNumber({}));
    EXPECT_NO_THROW(LargeNumber(base));
    EXPECT_NO_THROW(LargeNumber(zero));
    EXPECT_NO_THROW(LargeNumber(max8bit));
    EXPECT_NO_THROW(LargeNumber(vectorOfMaxes));
    EXPECT_NO_THROW(LargeNumber(vector));
    EXPECT_NO_THROW(LargeNumber(empty));
}

TEST(LARGE_NUMBER_ASSUMPTION, EMPTY_IS_UNIT) {
    LargeNumber empty = LargeNumber({});
    EXPECT_EQ(empty.vector().size(), 1);
}

TEST(LARGE_NUMBER_ASSUMPTION, RANDOM_ACCESS_IS_VALUE_SET) {
    LargeNumber zero = LargeNumber({0,1,2,3,4});
    LargeNumber one = LargeNumber({1,1,1,1,1});
    LargeNumber nine = LargeNumber({9,8,7,6,5});

    EXPECT_EQ(zero[0], 0);
    EXPECT_EQ(zero[1], 1);
    EXPECT_EQ(zero[2], 2);
    EXPECT_EQ(zero[3], 3);
    EXPECT_EQ(zero[4], 4);

    EXPECT_EQ(one[0], 1);
    EXPECT_EQ(one[1], 1);
    EXPECT_EQ(one[2], 1);
    EXPECT_EQ(one[3], 1);
    EXPECT_EQ(one[4], 1);

    EXPECT_EQ(nine[0], 9);
    EXPECT_EQ(nine[1], 8);
    EXPECT_EQ(nine[2], 7);
    EXPECT_EQ(nine[3], 6);
    EXPECT_EQ(nine[4], 5);
}

/**
 * EQUALITY OPERATIONS
 */
TEST(LARGE_NUMBER_EQUALITY, INEQUALITY) {
    LargeNumber a = LargeNumber({0,UINT8_MAX}), // 90
                b = LargeNumber({UINT8_MAX}), // 9
                c = LargeNumber(); // 0; 90>9>0; a > b > c
    EXPECT_TRUE(a > b); // 90 > 9
    EXPECT_FALSE(a < b);
    EXPECT_FALSE(a == b);

    EXPECT_TRUE(a > c);
    EXPECT_FALSE(a < c);
    EXPECT_FALSE(a == c);

    EXPECT_TRUE(c < b); // 0 < 9
    EXPECT_FALSE(c > b);
    EXPECT_FALSE(c == b);

    EXPECT_FALSE(a < a);
    EXPECT_FALSE(a > a);
    EXPECT_TRUE(a <= a);
    EXPECT_TRUE(a >= a);

    EXPECT_FALSE(b < b);
    EXPECT_FALSE(b > b);
    EXPECT_TRUE(b <= b);
    EXPECT_TRUE(b >= b);
    
    EXPECT_FALSE(c < c);
    EXPECT_FALSE(c > c);
    EXPECT_TRUE(c <= c);
    EXPECT_TRUE(c >= c);

    EXPECT_TRUE(LargeNumber({0,1,2,3,4,5}) < LargeNumber({1,1,2,3,4,5}));
    EXPECT_TRUE(LargeNumber({0,0,0,0,0,6}) > LargeNumber({1,1,2,3,4,5}));
}

TEST(LARGE_NUMBER_EQUALITY, EQUALITY) {
    LargeNumber consecutive = LargeNumber({0,1,2,3,4}); // 43,210 sort of. 
    LargeNumber built = LargeNumber();
    built[0] = 0;
    built[1] = 1;
    built[2] = 2;
    built[3] = 3;
    built[4] = 4;

    EXPECT_TRUE(built == consecutive);
    built[4] = 5;
    EXPECT_TRUE(built != consecutive);

    // VS Leading zeros
    EXPECT_FALSE(LargeNumber({0,0,1}) == LargeNumber({1}));
    EXPECT_TRUE(LargeNumber({1,0,0}) == LargeNumber({1}));
}

/**
 * BITWISE OPERATIONS
 */
TEST(LARGE_NUMBER_BITWISE, AND) {
    LargeNumber five_eights = LargeNumber({8,8,8,8,8}),
                five_nines = LargeNumber({9,9,9,9,9}),
                three_eights = LargeNumber({8,8,8}),
                zeros = LargeNumber();

    EXPECT_EQ(five_eights & five_nines, five_eights);
    EXPECT_EQ(five_nines & five_nines, five_nines);
    EXPECT_EQ(three_eights & five_eights, three_eights);
    EXPECT_EQ(zeros & five_eights, zeros);
}

TEST(LARGE_NUMBER_BITWISE, OR) {
    LargeNumber five_eights = LargeNumber({8,8,8,8,8}),
                five_nines = LargeNumber({9,9,9,9,9}),
                three_eights = LargeNumber({8,8,8}),
                zeros = LargeNumber();

    EXPECT_EQ(five_eights | five_nines, five_nines);
    EXPECT_EQ(five_nines | five_nines, five_nines);
    EXPECT_EQ(three_eights | five_eights, five_eights);
    EXPECT_EQ(zeros | five_eights, five_eights);
    EXPECT_EQ(zeros | zeros, zeros);
}

TEST(LARGE_NUMBER_BITWISE, NOT) {
    EXPECT_EQ(!LargeNumber({0,0,0,0}), LargeNumber({UINT8_MAX,UINT8_MAX,UINT8_MAX,UINT8_MAX}));
    EXPECT_EQ(!LargeNumber({1,1,1,1}), LargeNumber({UINT8_MAX-1,UINT8_MAX-1,UINT8_MAX-1,UINT8_MAX-1}));
    EXPECT_EQ(!LargeNumber({0x0f,0xf0,0x3c,0xc3}), LargeNumber({0xf0,0x0f,0xc3,0x3c}));
}

/**
 * ARITHMETIC OPERATIONS
 */
TEST(LARGE_NUMBER_UTILS, PLUS_HELPER) {
    // uint8_t plus_helper_(uint8_t a, uint8_t b, bool& c);
    auto EXPECTING_VALUE = [](  uint8_t a, uint8_t b, bool in_c, // plus_helper_ inputs
                                uint8_t out_n, bool out_c) { // outputs
        bool c = in_c; // value may be modified after plus_helper_ call

        EXPECT_EQ(out_n, plus_(a,b,c));
        EXPECT_EQ(out_c, c);
    };
    
    EXPECTING_VALUE(0,0,false,          0,false);
    EXPECTING_VALUE(0,0,true,           1,false);
    EXPECTING_VALUE(UINT8_MAX,0,true,   0,true);
    EXPECTING_VALUE(UINT8_MAX,1,false,  0,true);
    EXPECTING_VALUE(UINT8_MAX,1,true,   1,true);
    EXPECTING_VALUE(10,20,false,        30,false);
    EXPECTING_VALUE(10,20,true,         31,false);
}

TEST(LARGE_NUMBER_ARITHMETIC, PLUS_LARGE_NUMBER) {
    LargeNumber zero = LargeNumber({0,0,0,0,0});
    LargeNumber one = LargeNumber({1,1,1,1,1});
    LargeNumber max = LargeNumber({UINT8_MAX,UINT8_MAX,UINT8_MAX,UINT8_MAX,UINT8_MAX});

    EXPECT_EQ(LargeNumber({1}) + LargeNumber({1}), LargeNumber({2}));
    EXPECT_EQ(LargeNumber({0}) + LargeNumber({3}), LargeNumber({3}));

    EXPECT_EQ(zero + one, LargeNumber({1,1,1,1,1}));
    EXPECT_EQ(zero + max, LargeNumber({UINT8_MAX,UINT8_MAX,UINT8_MAX,UINT8_MAX,UINT8_MAX}));
    EXPECT_EQ(max + one, LargeNumber({0,1,1,1,1,1}));
}

TEST(LARGE_NUMBER_ARITHMETIC, MINUS_LARGE_NUMER) {
    LargeNumber zero = LargeNumber({0,0,0,0,0});
    LargeNumber one = LargeNumber({1,1,1,1,1});
    LargeNumber max = LargeNumber({UINT8_MAX,UINT8_MAX,UINT8_MAX,UINT8_MAX,UINT8_MAX});

    EXPECT_EQ(LargeNumber({1}) - LargeNumber({1}), LargeNumber({0}));
    // negatives are thrown away, given 0
    EXPECT_EQ(zero - one, LargeNumber({0,0,0,0,0}));
    EXPECT_EQ(one - one, LargeNumber({0,0,0,0,0}));
    EXPECT_EQ(max - one, LargeNumber({UINT8_MAX-1,UINT8_MAX-1,UINT8_MAX-1,UINT8_MAX-1,UINT8_MAX-1}));
    EXPECT_EQ(one - LargeNumber({2}), LargeNumber({UINT8_MAX,0,1,1,1}));
}