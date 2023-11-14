#include "gtest/gtest.h"
#include "sstream"
#include "myfigures.hpp"
#include "point2D.hpp"

TEST(TemplateTest, Triangles_Float) {
    Triangle<float> tr;
    tr.a = Point2D(1.5f, 2.0f);
    tr.b = Point2D(3.0f, 4.5f);
    tr.c = Point2D(0.0f, 0.0f);

    EXPECT_EQ(tr.a, Point2D<float>(1.5, 2.0));
    EXPECT_EQ(tr.b, Point2D<float>(3.0, 4.5));
    EXPECT_EQ(tr.c, Point2D<float>(0.0, 0.0));
}

TEST(TemplateTest, Triangles_Long) {
    Triangle<long> tr;
    tr.a = Point2D(10L, 20L);
    tr.b = Point2D(30L, 40L);
    tr.c = Point2D(0L, 0L);

    EXPECT_EQ(tr.a, Point2D<long>(10, 20));
    EXPECT_EQ(tr.b, Point2D<long>(30, 40));
    EXPECT_EQ(tr.c, Point2D<long>(0, 0));
}


TEST(TriangleTest, ConstructionFromStream) {
    std::stringstream ss("0, 0.0 2.0, 0 1, 2.0");
    Triangle<double> triangle;
    ss >> triangle;
    Point2D<double> center = triangle.center();
    ASSERT_DOUBLE_EQ(center.x(), 1.0);
    ASSERT_DOUBLE_EQ(center.y(), 2.0 / 3.0);
}

TEST(TriangleTest, MoveConstructor) {
    Triangle<double> original;
    original.a = Point2D<double>(1, 1);
    original.b = Point2D<double>(3.5, 5);
    original.c = Point2D<double>(1.5, 0);

    Triangle<double> copy = original;
    Triangle<double> moved = std::move(original);

    ASSERT_TRUE(moved == copy);  
    ASSERT_TRUE(original.a.x() == 1.0 && original.a.y() == 1.0); 
}

TEST(TriangleTest, Center) {
    Triangle<double> triangle;
    triangle.a = Point2D<double>(1, 1);
    triangle.b = Point2D<double>(3.5, 5);
    triangle.c = Point2D<double>(1.5, 0);
    Point2D center = triangle.center();
    ASSERT_DOUBLE_EQ(center.x(), 2.0);
    ASSERT_DOUBLE_EQ(center.y(), 2.0);
}

TEST(TriangleTest, Equality) {
    Triangle<double> triangle1;
    triangle1.a.set(0.0, 0.0);
    triangle1.b.set(2.0, 0.0);
    triangle1.c.set(1.0, 2.0);

    Triangle<double> triangle2;
    triangle2.a.set(0.0, 0.0);
    triangle2.b.set(2.0, 0.0);
    triangle2.c.set(1.0, 2.0);

    ASSERT_TRUE(triangle1 == triangle2);
}

TEST(TriangleTest, Area) {
    Triangle<double> triangle;
    triangle.a = Point2D<double>(1, 1);
    triangle.b = Point2D<double>(-2, 4);
    triangle.c = Point2D<double>(-2, -2);
    EXPECT_NEAR(double(triangle), 9.0, 0.01);
}

TEST(TriangleTest, Assignation) {
    Triangle<double> triangle;
    triangle.a = Point2D<double>(1, 1);
    triangle.b = Point2D<double>(-2, 4);
    triangle.c = Point2D<double>(-2, -2);

    Triangle<double> tr2 = triangle;
    EXPECT_NEAR(double(triangle), 9.0, 0.01);
    ASSERT_TRUE(triangle == tr2);
    Point2D center = tr2.center();
    EXPECT_DOUBLE_EQ(center.x(), -1);
    EXPECT_DOUBLE_EQ(center.y(), 1);
}

TEST(RectangleTest, ConstructionFromStream) {
    std::stringstream ss("0, 0.0 4.0, 0 4.0, 3.0 0, 3.0");
    Rectangle<double> rectangle;
    ss >> rectangle;
    Point2D<double> center = rectangle.center();
    ASSERT_DOUBLE_EQ(center.x(), 2.0);
    ASSERT_DOUBLE_EQ(center.y(), 1.5);
}

TEST(RectangleTest, Center) {
    Rectangle<double> rectangle;
    rectangle.a = Point2D<double>(0, 0);
    rectangle.b = Point2D<double>(4, 0);
    rectangle.c = Point2D<double>(4, 3);
    rectangle.d = Point2D<double>(0, 3);
    Point2D<double> center = rectangle.center();
    ASSERT_DOUBLE_EQ(center.x(), 2.0);
    ASSERT_DOUBLE_EQ(center.y(), 1.5);
}

TEST(RectangleTest, Equality) {
    Rectangle<double> rect1;
    rect1.a.set(0.0, 0.0);
    rect1.b.set(4.0, 0.0);
    rect1.c.set(4.0, 3.0);
    rect1.d.set(0.0, 3.0);

    Rectangle<double> rect2;
    rect2.a.set(0.0, 0.0);
    rect2.b.set(4.0, 0.0);
    rect2.c.set(4.0, 3.0);
    rect2.d.set(0.0, 3.0);

    ASSERT_TRUE(rect1 == rect2);
}

TEST(RectangleTest, Area) {
    Rectangle<double> rectangle;
    rectangle.a = Point2D<double>(0, 0);
    rectangle.b = Point2D<double>(4, 0);
    rectangle.c = Point2D<double>(4, 3);
    rectangle.d = Point2D<double>(0, 3);
    ASSERT_DOUBLE_EQ(double(rectangle), 12.0);
}

TEST(SquareTest, ConstructionFromStream) {
    std::stringstream ss("1, 1 2, 1 2, 2 1, 2");
    Square<double> square;
    ss >> square;
    Point2D<double> center = square.center();
    ASSERT_DOUBLE_EQ(center.x(), 1.5);
    ASSERT_DOUBLE_EQ(center.y(), 1.5);
}

TEST(SquareTest, Center) {
    Square<double> square;
    square.a = Point2D<double>(1, 1);
    square.b = Point2D<double>(2, 1);
    square.c = Point2D<double>(2, 2);
    square.d = Point2D<double>(1, 2);
    Point2D<double> center = square.center();
    ASSERT_DOUBLE_EQ(center.x(), 1.5);
    ASSERT_DOUBLE_EQ(center.y(), 1.5);
}

TEST(SquareTest, Equality) {
    Square<double> square1;
    square1.a.set(1.0, 1.0);
    square1.b.set(2.0, 1.0);
    square1.c.set(2.0, 2.0);
    square1.d.set(1.0, 2.0);

    Square<double> square2;
    square2.a.set(1.0, 1.0);
    square2.b.set(2.0, 1.0);
    square2.c.set(2.0, 2.0);
    square2.d.set(1.0, 2.0);

    ASSERT_TRUE(square1 == square2);
}

TEST(SquareTest, Area) {
    Square<double> square;
    square.a = Point2D<double>(1, 1);
    square.b = Point2D<double>(2, 1);
    square.c = Point2D<double>(2, 2);
    square.d = Point2D<double>(1, 2);
    ASSERT_NEAR(double(square), 1.0, 0.01);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
