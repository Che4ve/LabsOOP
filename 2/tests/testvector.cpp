#include "gtest/gtest.h"
#include "../include/vector13.h"

// Test the default constructor
TEST(Vector13ConstructorTest, DefaultConstructor) {
    Vector13 v;
    EXPECT_EQ(v.size(), 0);
    EXPECT_TRUE(v.isEmpty());
    EXPECT_EQ(v.str(), "");
}

// Test the constructor with capacity
TEST(Vector13ConstructorTest, ConstructorWithCapacity) {
    Vector13 v(10);
    EXPECT_EQ(v.size(), 0);
    EXPECT_TRUE(v.isEmpty());
    EXPECT_EQ(v.str(), "");
}

// Test the constructor with a string
TEST(Vector13ConstructorTest, ConstructorWithString) {
    Vector13 v("  Hello 13!");
    EXPECT_EQ(v.size(), 9); 
    EXPECT_FALSE(v.isEmpty());
    EXPECT_EQ(v.str(), "HELLO 13!");
}

// Test the size and isEmpty methods
TEST(Vector13SizeTest, SizeAndIsEmpty) {
    Vector13 v;
    EXPECT_EQ(v.size(), 0);
    EXPECT_TRUE(v.isEmpty());

    v.pushBack('A');
    EXPECT_EQ(v.size(), 1);
    EXPECT_FALSE(v.isEmpty());
}

// Test the pushBack method
TEST(Vector13PushBackTest, PushBack) {
    Vector13 v;
    v.pushBack('A');
    v.pushBack('B');
    v.pushBack('C');

    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v.str(), "ABC");
}

// Test the reserve method
TEST(Vector13ReserveTest, Reserve) {
    Vector13 v;
    v.reserve(5);

    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.str(), "");

    v.pushBack('A');
    v.reserve(10);

    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v.str(), "A");
}

// Test the clear method
TEST(Vector13ClearTest, Clear) {
    Vector13 v;
    v.pushBack('A');
    v.pushBack('B');
    v.pushBack('C');

    EXPECT_EQ(v.size(), 3);

    v.clear();

    EXPECT_EQ(v.size(), 0);
    EXPECT_TRUE(v.isEmpty());
}

// Test the reverse method
TEST(Vector13ReverseTest, Reverse) {
    Vector13 v;
    v.pushBack('A');
    v.pushBack('B');
    v.pushBack('C');

    EXPECT_EQ(v.str(), "ABC");

    v.reverse();

    EXPECT_EQ(v.str(), "CBA");
}

// Test the subscript operator
TEST(Vector13SubscriptTest, SubscriptOperator) {
    Vector13 v("HELLO");
    
    EXPECT_EQ(v[0], 'H');
    EXPECT_EQ(v[3], 'L');
    EXPECT_EQ(v[10], '\0'); // Out of bounds, should return null character
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
