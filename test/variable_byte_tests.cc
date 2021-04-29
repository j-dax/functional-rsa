#include <gtest/gtest.h>
#include "variable_byte_unsigned_integer.h"

TEST(VARIABLE_BYTE_INTEGER, BASIC_INSTANTIATION_THROWS_NO_ERRORS) {
    VariableByteUnsignedInteger a;
    VariableByteUnsignedInteger v = VariableByteUnsignedInteger();
    a = v;

    std::vector<Number> vec = {1,2,3,4,5};
    VariableByteUnsignedInteger b = vec;
    VariableByteUnsignedInteger c(vec);
}

TEST(VARIABLE_BYTE_INTEGER, UNINSTANTIATED_NUMBER_RETURNS_ZERO) {
    VariableByteUnsignedInteger a;
    EXPECT_EQ(0, a[0]);
    EXPECT_EQ(0, a[127]);
}

TEST(VARIABLE_BYTE_INTEGER, DIRECT_ASSIGNMENT_VALUE_CHECK) {
    VariableByteUnsignedInteger a;
    EXPECT_EQ(0, a[0]);

    a[0]=10;
    EXPECT_EQ(10, a[0]);

    a[0]=1;
    a[1]=11;
    a[2]=12;
    a[3]=66;

    EXPECT_EQ(1, a[0]);
    EXPECT_EQ(11, a[1]);
    EXPECT_EQ(12, a[2]);
    EXPECT_EQ(66, a[3]);
}

TEST(VARIABLE_BYTE_INTEGER, INSTANTIATED_VALUES_ARE_ORDERED) {
    std::vector<Number> vec = {1,2,3,4,5};
    VariableByteUnsignedInteger b(vec); // std::vector
    for (int i = 0; i < vec.size(); i++) {
        EXPECT_EQ(vec[i], b[i]);
    }
}

TEST(VARIABLE_BYTE_INTEGER, ADD_CARRYOVER) {
    std::vector<Number> vec = {9,9,9};
    VariableByteUnsignedInteger b(vec),c;
    c=b+{1};
}