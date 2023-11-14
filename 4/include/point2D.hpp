#pragma once

#include <iostream>

template <class T>
class Point2D {
    private:
        T _x, _y;

    public:
        Point2D() : _x(0), _y(0) {}
        Point2D(T x, T y) : _x(x), _y(y) {}
        Point2D(Point2D&& other) noexcept;

        void set(T x, T y);

        void x(T x);
        void y(T y);

        T x() const;
        T y() const;

        T distanceTo(const Point2D& other) const;
        T dotProduct(const Point2D& other) const;

        bool operator==(const Point2D& other) const;
        
        friend const Point2D operator+(const Point2D& p1, const Point2D& p2) {
            return Point2D<T>(p1._x + p2._x, p1._y + p2._y);
        }
        friend const Point2D operator-(const Point2D& p1, const Point2D& p2) {
            return Point2D<T>(p1._x - p2._x, p1._y - p2._y);
        }

        Point2D& operator=(const Point2D& other);

        friend std::istream& operator>>(std::istream& is, Point2D& point) {
            double x, y;
            char comma;
            is >> x >> comma >> y;
            point.set(x, y);
            return is;
        }

        friend std::ostream& operator<<(std::ostream& os, const Point2D& point) {
            os << '(' << point.x() << " , " << point.y() << ')';
            return os;
        }   
    
};

#include "../templates/point2D.tpp"