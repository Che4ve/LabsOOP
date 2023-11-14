#include "./figure.hpp"

template <class T>
class Triangle : public Figure {
    public:
        Point2D<T> a, b, c;
        Triangle();
        Triangle(const Triangle& other);
        ~Triangle() = default;

        Point2D<T> center();
        
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

template <class T>
class Rectangle : public Figure {
    public:
        Point2D<T> a, b, c, d;
        Rectangle();
        Rectangle(const Rectangle& other);
        ~Rectangle() = default;

        Point2D<T> center();

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

template <class T>
class Square : public Rectangle<T> {
    public:
        Square();
        ~Square() = default;

    protected:
        void readVertices(std::istream& is) override;
};

#include "../templates/myfigures.tpp"