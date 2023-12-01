#include <gtest/gtest.h>
#include "iterators.hpp" 
#include "myqueue.hpp"

TEST(IteratorTest, IteratorInitialization) {
    // Test initializing Iterator with a pointer
    Node<int> node1(10);
    Iterator<Node<int>> iterator1(&node1);

    EXPECT_EQ((*iterator1).data, 10);
}

TEST(IteratorTest, IteratorIncrement) {
    // Test prefix increment of Iterator
    Node<int> node1(10);
    Node<int> node2(20);

    node1.next = &node2;

    Iterator<Node<int>> iterator1(&node1);
    ++iterator1;

    EXPECT_EQ((*iterator1).data, 20);

    // Test postfix increment of Iterator
    Iterator<Node<int>> iterator2(&node1);
    Iterator<Node<int>> iterator3 = iterator2++;

    EXPECT_EQ((*iterator2).data, 20);
    EXPECT_EQ((*iterator3).data, 10);
}

TEST(ConstIteratorTest, ConstIteratorInitialization) {
    // Test initializing ConstIterator with a const pointer
    Node<int> node1(10);
    ConstIterator<Node<int>> constIterator1(&node1);

    EXPECT_EQ((*constIterator1).data, Node<int>(10).data);
}

TEST(ConstIteratorTest, ConstIteratorIncrement) {
    // Test prefix increment of ConstIterator
    Node<int> node1(10);
    Node<int> node2(20);

    node1.next = &node2;

    ConstIterator<Node<int>> constIterator1(&node1);
    ++constIterator1;

    EXPECT_EQ((*constIterator1).data, 20);

    // Test postfix increment of ConstIterator
    ConstIterator<Node<int>> constIterator2(&node1);
    ConstIterator<Node<int>> constIterator3 = constIterator2++;

    EXPECT_EQ((*constIterator2).data, 20);
    EXPECT_EQ((*constIterator3).data, 10);
}

TEST(IteratorTest, IteratorEquality) {
    Node<int> node1(10);
    Node<int> node2(20);
    Node<int> node3(30);

    node1.next = &node2;
    node2.next = &node3;

    Iterator<Node<int>> iterator1(&node1);
    Iterator<Node<int>> iterator2(&node1);
    Iterator<Node<int>> iterator3(&node2);

    // Test equality
    EXPECT_TRUE(iterator1 == iterator2);
    EXPECT_FALSE(iterator1 == iterator3);
}

TEST(ConstIteratorTest, ConstIteratorEquality) {
    Node<int> node1(10);
    Node<int> node2(20);
    Node<int> node3(30);

    node1.next = &node2;
    node2.next = &node3;

    ConstIterator<Node<int>> constIterator1(&node1);
    ConstIterator<Node<int>> constIterator2(&node1);
    ConstIterator<Node<int>> constIterator3(&node2);

    // Test equality
    EXPECT_TRUE(constIterator1 == constIterator2);
    EXPECT_FALSE(constIterator1 == constIterator3);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
