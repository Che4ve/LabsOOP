#include <gtest/gtest.h>
#include "myqueue.hpp"

TEST(MyQueueTest, QueueInitialization) {
    // Test initializing an empty queue
    MyQueue<int> queue;

    EXPECT_TRUE(queue.empty());
}

TEST(MyQueueTest, QueuePushAndFront) {
    // Test pushing elements and getting front element
    MyQueue<int> queue;

    queue.push(10);
    queue.push(20);

    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.front(), 10);
}

TEST(MyQueueTest, QueuePop) {
    // Test pushing elements, popping, and checking if empty
    MyQueue<int> queue;

    queue.push(10);
    queue.push(20);
    queue.pop();

    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.front(), 20);

    queue.pop();

    EXPECT_TRUE(queue.empty());
}

TEST(MyQueueTest, QueueIteration) {
    // Test iterating through the queue
    MyQueue<int> queue;

    queue.push(10);
    queue.push(20);
    queue.push(30);

    std::vector<int> elements;

    for (const auto& node : queue) {
        elements.push_back(node.data);
    }

    std::vector<int> comp{10,20,30};

    EXPECT_EQ(elements, comp);
}

TEST(MyQueueTest, QueueConstIteration) {
    // Test const iteration through the queue
    const MyQueue<int> queue_const;

    // Add some elements to the const queue
    const_cast<MyQueue<int>&>(queue_const).push(10);
    const_cast<MyQueue<int>&>(queue_const).push(20);
    const_cast<MyQueue<int>&>(queue_const).push(30);

    std::vector<int> elements;

    for (const auto& node : queue_const) {
        elements.push_back(node.data);
    }

    std::vector<int> comp{10,20,30};

    EXPECT_EQ(elements, comp);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
