#include <iostream>
#include <cmath>
#include "./point2D.h"

class Figure {
    public:
        Figure() = default;
        Figure(const Figure& other) = default;

        virtual Point2D center() = 0;

        friend std::ostream& operator<<(std::ostream& os, const Figure& figure) {
            figure.printVertices(os);
            return os;
        }

        friend std::istream& operator>>(std::istream& is, Figure& figure) {
            figure.readVertices(is);
            return is;
        }

        Figure& operator=(const Figure& other) {
            if (this != &other){
                _copy(other);
            }
            return *this;
        }

        Figure& operator=(Figure&& other) {
            if (this != &other){
                _move(other);
            }
            return *this;
        }

        bool operator==(const Figure& other) const {
            return isSameAs(other);
        }

        operator double() const {
            return getArea();
        }

        virtual ~Figure() {};

    protected:
        virtual void printVertices(std::ostream& os) const = 0;
        virtual void readVertices(std::istream& is) = 0;

        virtual Figure& _copy(const Figure& other) = 0;
        virtual Figure& _move(Figure& other) = 0;

        virtual bool isSameAs(const Figure& other) const = 0;

        virtual double getArea() const = 0;

};