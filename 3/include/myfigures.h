#include "./figure.h"

class Triangle : public Figure {
    public:
        Point2D a;
        Point2D b;
        Point2D c;

        Triangle();
        Triangle(const Triangle& other);
        ~Triangle() = default;

        Point2D center() override;

    protected:
        void printVertices(std::ostream& os) const override;
        void readVertices(std::istream& is) override;
        Figure& _copy(const Figure& other) override;
        Figure& _move(Figure& other) override;
        bool isSameAs(const Figure& other) const override;
        double getArea() const override;

    private:
        double sideA;
        double sideB;
        double sideC;

};

class Rectangle : public Figure {
    public:
        Point2D a;
        Point2D b;
        Point2D c;
        Point2D d;
        Rectangle();
        Rectangle(const Rectangle& other);
        ~Rectangle() = default;

        Point2D center() override;

    protected:
        void printVertices(std::ostream& os) const override;
        void readVertices(std::istream& is) override;
        Figure& _copy(const Figure& other) override;
        Figure& _move(Figure& other) override;
        bool isSameAs(const Figure& other) const override;
        double getArea() const override;

    private:
        double sideA;
        double sideB;
    
};

class Square : public Rectangle {
    public:
        Square();
        ~Square() = default;
        
    protected:
        void readVertices(std::istream& is) override;
};