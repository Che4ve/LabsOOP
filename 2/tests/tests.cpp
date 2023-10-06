#include "gtest/gtest.h"
#include "../include/thirteen.h"

// Test constructor Thirteen::Thirteen()
TEST(ThirteenConstructorTest, DefaultConstructor) {
    Thirteen thirteen;
    EXPECT_EQ(0, thirteen.inTenBase());
    EXPECT_EQ("0", thirteen.get());
}

// Test constructor Thirteen::Thirteen(int tenBaseNum)
TEST(ThirteenConstructorTest, IntegerConstructor_01) {
    Thirteen thirteen(13);
    EXPECT_EQ(13, thirteen.inTenBase());
    EXPECT_EQ("10", thirteen.get());
}
// Test constructor Thirteen::Thirteen(int tenBaseNum)
TEST(ThirteenConstructorTest, IntegerConstructor_02) {
    Thirteen thirteen(145);
    EXPECT_EQ(145, thirteen.inTenBase());
    EXPECT_EQ("B2", thirteen.get());
}

// Test constructor Thirteen::Thirteen(const char* str13base)
TEST(ThirteenConstructorTest, StringConstructorValid_01) {
    Thirteen thirteen("10");
    EXPECT_EQ(13, thirteen.inTenBase());
    EXPECT_EQ("10", thirteen.get());
}
// Test constructor Thirteen::Thirteen(const char* str13base)
TEST(ThirteenConstructorTest, StringConstructorValid_02) {
    Thirteen thirteen("abab");
    EXPECT_EQ(23970, thirteen.inTenBase());
    EXPECT_EQ("ABAB", thirteen.get());
}
// Test constructor Thirteen::Thirteen(const char* str13base)
TEST(ThirteenConstructorTest, StringConstructorInvalid) {
    Thirteen thirteen("G"); // Invalid character
    EXPECT_EQ(0, thirteen.inTenBase());
    EXPECT_EQ("0", thirteen.get());
}

// Test Thirteen::set(int tenBaseNum)
TEST(ThirteenSetTest, SetInteger) {
    Thirteen thirteen;
    thirteen.set(2023);
    EXPECT_EQ(2023, thirteen.inTenBase());
    EXPECT_EQ("BC8", thirteen.get());
}

// Test Thirteen::set(const char* str13base)
TEST(ThirteenSetTest, SetStringValid) {
    Thirteen thirteen;
    thirteen.set("10");
    EXPECT_EQ(13, thirteen.inTenBase());
    EXPECT_EQ("10", thirteen.get());
}
// Test Thirteen::set(const char* str13base)
TEST(ThirteenSetTest, SetStringInvalid) {
    Thirteen thirteen;
    thirteen.set("I"); // Invalid character
    EXPECT_EQ(0, thirteen.inTenBase());
    EXPECT_EQ("0", thirteen.get());
}

// Test addition
TEST(ThirteenAlgebraTest, AddTwoThirteens) {
    Thirteen a("aba");
    Thirteen b("1abc");
    Thirteen res;
    res = a + b;
    EXPECT_EQ(5885, res.inTenBase());
    EXPECT_EQ("28A9", res.get());
}

// Add more test cases for other methods as needed

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
