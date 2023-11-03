#include "vector.h"  // Include the class header
#include "gtest/gtest.h"

TEST(VectorTest, DefaultConstructor) {
    Vector<int> vec;
    EXPECT_EQ(vec.get_size(), 0);
    EXPECT_EQ(vec.begin(), vec.end());
}

TEST(VectorTest, PushBack) {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    EXPECT_EQ(vec.get_size(), 2);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
}

TEST(VectorTest, Erase) {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.erase(1);
    EXPECT_EQ(vec.get_size(), 2);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 3);
}

TEST(VectorTest, CopyConstructor) {
    Vector<int> original;
    original.push_back(1);
    original.push_back(2);
    Vector<int> copied(original);
    EXPECT_EQ(copied.get_size(), 2);
    EXPECT_EQ(copied[0], 1);
    EXPECT_EQ(copied[1], 2);
}

TEST(VectorTest, OperatorIndex) {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
