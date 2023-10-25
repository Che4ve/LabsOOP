#pragma once

#include <iostream>

class Point2D {
    private:
        double _x, _y;

    public:
        Point2D();
        Point2D(double x, double y);
        Point2D(Point2D&& other) noexcept;

        void set(double x, double y);

        void x(double x);
        void y(double y);

        double x() const;
        double y() const;

        double distanceTo(const Point2D& other) const;
        double dotProduct(const Point2D& other) const;

        bool operator==(const Point2D& other) const;
        
        friend const Point2D operator+(const Point2D& p1, const Point2D& p2);
        friend const Point2D operator-(const Point2D& p1, const Point2D& p2);

        Point2D& operator=(const Point2D& other);

        friend std::istream& operator>>(std::istream& is, Point2D& point);
        friend std::ostream& operator<<(std::ostream& os, const Point2D& point);
        
    
};