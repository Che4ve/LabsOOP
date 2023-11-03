#include "gtest/gtest.h"
#include "sstream"
#include "myfigures.h"
#include "point2D.h"

TEST(TriangleTest, ConstructionFromStream) {
    std::stringstream ss("0, 0.0 2.0, 0 1, 2.0");
    Triangle triangle;
    ss >> triangle;
    Point2D center = triangle.center();
    ASSERT_DOUBLE_EQ(center.x(), 1.0);
    ASSERT_DOUBLE_EQ(center.y(), 2.0 / 3.0);
}

TEST(TriangleTest, MoveConstructor) {
    Triangle original;
    original.a = Point2D(1, 1);
    original.b = Point2D(3.5, 5);
    original.c = Point2D(1.5, 0);

    Triangle copy = original;
    Triangle moved = std::move(original);

    ASSERT_TRUE(moved == copy);  
    ASSERT_TRUE(original.a.x() == 1.0 && original.a.y() == 1.0); 
}

TEST(TriangleTest, Center) {
    Triangle triangle;
    triangle.a = Point2D(1, 1);
    triangle.b = Point2D(3.5, 5);
    triangle.c = Point2D(1.5, 0);
    Point2D center = triangle.center();
    ASSERT_DOUBLE_EQ(center.x(), 2.0);
    ASSERT_DOUBLE_EQ(center.y(), 2.0);
}

TEST(TriangleTest, Equality) {
    Triangle triangle1;
    triangle1.a.set(0.0, 0.0);
    triangle1.b.set(2.0, 0.0);
    triangle1.c.set(1.0, 2.0);

    Triangle triangle2;
    triangle2.a.set(0.0, 0.0);
    triangle2.b.set(2.0, 0.0);
    triangle2.c.set(1.0, 2.0);

    ASSERT_TRUE(triangle1 == triangle2);
}

TEST(TriangleTest, Area) {
    Triangle triangle;
    triangle.a = Point2D(1, 1);
    triangle.b = Point2D(-2, 4);
    triangle.c = Point2D(-2, -2);
    ASSERT_DOUBLE_EQ(double(triangle), 9.0);
}

TEST(TriangleTest, Assignation) {
    Triangle triangle;
    triangle.a = Point2D(1, 1);
    triangle.b = Point2D(-2, 4);
    triangle.c = Point2D(-2, -2);

    Triangle tr2 = triangle;
    ASSERT_DOUBLE_EQ(double(tr2), 9.0);
    ASSERT_TRUE(triangle == tr2);
    Point2D center = tr2.center();
    ASSERT_DOUBLE_EQ(center.x(), -1);
    ASSERT_DOUBLE_EQ(center.y(), 1);
}

TEST(RectangleTest, ConstructionFromStream) {
    std::stringstream ss("0, 0.0 4.0, 0 4.0, 3.0 0, 3.0");
    Rectangle rectangle;
    ss >> rectangle;
    Point2D center = rectangle.center();
    ASSERT_DOUBLE_EQ(center.x(), 2.0);
    ASSERT_DOUBLE_EQ(center.y(), 1.5);
}

TEST(RectangleTest, Center) {
    Rectangle rectangle;
    rectangle.a = Point2D(0, 0);
    rectangle.b = Point2D(4, 0);
    rectangle.c = Point2D(4, 3);
    rectangle.d = Point2D(0, 3);
    Point2D center = rectangle.center();
    ASSERT_DOUBLE_EQ(center.x(), 2.0);
    ASSERT_DOUBLE_EQ(center.y(), 1.5);
}

TEST(RectangleTest, Equality) {
    Rectangle rect1;
    rect1.a.set(0.0, 0.0);
    rect1.b.set(4.0, 0.0);
    rect1.c.set(4.0, 3.0);
    rect1.d.set(0.0, 3.0);

    Rectangle rect2;
    rect2.a.set(0.0, 0.0);
    rect2.b.set(4.0, 0.0);
    rect2.c.set(4.0, 3.0);
    rect2.d.set(0.0, 3.0);

    ASSERT_TRUE(rect1 == rect2);
}

TEST(RectangleTest, Area) {
    Rectangle rectangle;
    rectangle.a = Point2D(0, 0);
    rectangle.b = Point2D(4, 0);
    rectangle.c = Point2D(4, 3);
    rectangle.d = Point2D(0, 3);
    ASSERT_DOUBLE_EQ(double(rectangle), 12.0);
}

TEST(SquareTest, ConstructionFromStream) {
    std::stringstream ss("1, 1 2, 1 2, 2 1, 2");
    Square square;
    ss >> square;
    Point2D center = square.center();
    ASSERT_DOUBLE_EQ(center.x(), 1.5);
    ASSERT_DOUBLE_EQ(center.y(), 1.5);
}

TEST(SquareTest, Center) {
    Square square;
    square.a = Point2D(1, 1);
    square.b = Point2D(2, 1);
    square.c = Point2D(2, 2);
    square.d = Point2D(1, 2);
    Point2D center = square.center();
    ASSERT_DOUBLE_EQ(center.x(), 1.5);
    ASSERT_DOUBLE_EQ(center.y(), 1.5);
}

TEST(SquareTest, Equality) {
    Square square1;
    square1.a.set(1.0, 1.0);
    square1.b.set(2.0, 1.0);
    square1.c.set(2.0, 2.0);
    square1.d.set(1.0, 2.0);

    Square square2;
    square2.a.set(1.0, 1.0);
    square2.b.set(2.0, 1.0);
    square2.c.set(2.0, 2.0);
    square2.d.set(1.0, 2.0);

    ASSERT_TRUE(square1 == square2);
}

TEST(SquareTest, Area) {
    Square square;
    square.a = Point2D(1, 1);
    square.b = Point2D(2, 1);
    square.c = Point2D(2, 2);
    square.d = Point2D(1, 2);
    ASSERT_DOUBLE_EQ(double(square), 1.0);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
