#include "gtest/gtest.h"
#include "../include/thirteen.h"

// === CONSTRUCTOR TEST ===

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

// === SETTER TEST ===

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
    // Invalid character
    ASSERT_THROW(thirteen.set("I"), std::invalid_argument);
}

// === ALGEBRA (OPERATORS) TEST ===

// Test addition
TEST(ThirteenAlgebraTest, AddTwoThirteens) {
    Thirteen a("aba");
    Thirteen b("1abc");
    Thirteen res;
    res = a + b;
    EXPECT_EQ(5885, res.inTenBase());
    EXPECT_EQ("28A9", res.get());
}
// Test subtraction
TEST(ThirteenAlgebraTest, SubtractTwoThirteens_01) {
    Thirteen a(100);
    Thirteen b(10);
    Thirteen res;
    res = a - b;
    EXPECT_EQ(90, res.inTenBase());
    EXPECT_EQ("6C", res.get());
}
// Test subtraction
TEST(ThirteenAlgebraTest, SubtractTwoThirteens_02) {
    Thirteen a(10);
    Thirteen b(100);
    Thirteen res;
    res = a - b;
    EXPECT_EQ(0, res.inTenBase());
    EXPECT_EQ("0", res.get());
}
// Test +=
TEST(ThirteenAlgebraTest, AssignWithAddition_01) {
    Thirteen a(10);
    Thirteen b(100);
    a += b;
    EXPECT_EQ(110, a.inTenBase());
    EXPECT_EQ("86", a.get());
}
// Test -=
TEST(ThirteenAlgebraTest, AssignWithSubtraction_01) {
    Thirteen a(100);
    Thirteen b(10);
    a -= b;
    EXPECT_EQ(90, a.inTenBase());
    EXPECT_EQ("6C", a.get());
}
// Test -=
TEST(ThirteenAlgebraTest, AssignWithSubtraction_02) {
    Thirteen a(10);
    Thirteen b(100);
    a -= b;
    EXPECT_EQ(0, a.inTenBase());
    EXPECT_EQ("0", a.get());
}

// === COMPARISON OPERATORS TEST ===

// Test >
TEST(ThirteenCompareTest, MoreThan_01) {
    Thirteen a(100);
    Thirteen b(10);
    ASSERT_TRUE(a > b);
}
// Test >
TEST(ThirteenCompareTest, MoreThan_02) {
    Thirteen a(10);
    Thirteen b(100);
    ASSERT_FALSE(a > b);
}

// Test <
TEST(ThirteenCompareTest, LessThan_01) {
    Thirteen a(10);
    Thirteen b(100);
    ASSERT_TRUE(a < b);
}
// Test <
TEST(ThirteenCompareTest, LessThan_02) {
    Thirteen a(100);
    Thirteen b(10);
    ASSERT_FALSE(a < b);
}

// Test ==
TEST(ThirteenCompareTest, Equals_01) {
    Thirteen a(100);
    Thirteen b(100);
    ASSERT_TRUE(a == b);
}
// Test ==
TEST(ThirteenCompareTest, Equals_02) {
    Thirteen a(10);
    Thirteen b(100);
    ASSERT_FALSE(a == b);
}
// Test ==
TEST(ThirteenCompareTest, Equals_03) {
    Thirteen a(100);
    Thirteen b(10);
    ASSERT_FALSE(a == b);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
