#include <gtest/gtest.h>
#include "allocator.hpp" 

TEST(CustomAllocatorTest, AllocateAndDeallocate) {
    CustomAllocator<int, 5> allocator;

    int* ptr1 = allocator.allocate(1);
    EXPECT_NE(ptr1, nullptr);

    int* ptr2 = allocator.allocate(2);
    EXPECT_NE(ptr2, nullptr);

    allocator.deallocate(ptr1, 1);
    allocator.deallocate(ptr2, 2);
}

TEST(CustomAllocatorTest, AllocateBeyondCapacity) {
    CustomAllocator<int, 2> allocator;

    int* ptr1 = allocator.allocate(1);
    EXPECT_NE(ptr1, nullptr);

    int* ptr2 = allocator.allocate(1);
    EXPECT_NE(ptr2, nullptr);

    // Trying to allocate beyond capacity should throw an exception
    EXPECT_THROW(allocator.allocate(1), std::runtime_error);

    allocator.deallocate(ptr1, 1);
    allocator.deallocate(ptr2, 1);
}

TEST(CustomAllocatorTest, AllocateDeallocateMultipleObjects) {
    CustomAllocator<double, 3> allocator;

    double* ptr1 = allocator.allocate(1);
    double* ptr2 = allocator.allocate(1);

    EXPECT_NE(ptr1, nullptr);
    EXPECT_NE(ptr2, nullptr);
    EXPECT_NE(ptr1, ptr2);  // Ensure different addresses

    allocator.deallocate(ptr1, 1);
    allocator.deallocate(ptr2, 1);
}

TEST(CustomAllocatorTest, AllocateDeallocateVector) {
    CustomAllocator<std::string, 4> allocator;

    std::string* str1 = allocator.allocate(1);
    std::string* str2 = allocator.allocate(1);

    *str1 = "Hello";
    *str2 = "World";

    EXPECT_EQ(*str1, "Hello");
    EXPECT_EQ(*str2, "World");

    allocator.deallocate(str1, 1);
    allocator.deallocate(str2, 1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
