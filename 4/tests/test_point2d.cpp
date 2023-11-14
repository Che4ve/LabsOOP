#include "point2D.hpp"  // Include the class header
#include "gtest/gtest.h"

TEST(Point2DTest, DefaultConstructor) {
    Point2D<double> point;
    ASSERT_EQ(point.x(), 0.0);
    ASSERT_EQ(point.y(), 0.0);
}

TEST(Point2DTest, ParameterizedConstructor) {
    Point2D point(2.0, 3.0);
    ASSERT_EQ(point.x(), 2.0);
    ASSERT_EQ(point.y(), 3.0);
}

TEST(Point2DTest, SetXAndY) {
    Point2D<double> point;
    point.x(4.0);
    point.y(5.0);
    ASSERT_EQ(point.x(), 4.0);
    ASSERT_EQ(point.y(), 5.0);
}

TEST(Point2DTest, DistanceTo) {
    Point2D point1(1.0, 2.0);
    Point2D point2(4.0, 6.0);
    ASSERT_DOUBLE_EQ(point1.distanceTo(point2), 5.0);
}

TEST(Point2DTest, DotProduct) {
    Point2D point1(2.0, 3.0);
    Point2D point2(4.0, 5.0);
    ASSERT_DOUBLE_EQ(point1.dotProduct(point2), 23.0);
}

TEST(Point2DTest, Equality) {
    Point2D point1(2.0, 3.0);
    Point2D point2(2.0, 3.0);
    Point2D point3(4.0, 5.0);
    ASSERT_TRUE(point1 == point2);
    ASSERT_FALSE(point1 == point3);
}

TEST(Point2DTest, AssignmentOperator) {
    Point2D point1(2.0, 3.0);
    Point2D point2(4.0, 5.0);
    point2 = point1;
    ASSERT_EQ(point2.x(), 2.0);
    ASSERT_EQ(point2.y(), 3.0);
}

TEST(Point2DTest, AdditionOperator) {
    Point2D point1(2.0, 3.0);
    Point2D point2(4.0, 5.0);
    Point2D result = point1 + point2;
    ASSERT_EQ(result.x(), 6.0);
    ASSERT_EQ(result.y(), 8.0);
}

TEST(Point2DTest, SubtractionOperator) {
    Point2D point1(4.0, 5.0);
    Point2D point2(2.0, 3.0);
    Point2D result = point1 - point2;
    ASSERT_EQ(result.x(), 2.0);
    ASSERT_EQ(result.y(), 2.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
