#include "../include/point2D.h"

Point2D::Point2D() : _x(0), _y(0) {};

Point2D::Point2D(double x, double y) : _x(x), _y(y) {};

Point2D::Point2D(Point2D&& other) noexcept {
    _x = std::move(other._x);
    _y = std::move(other._y);
}

void Point2D::set(double x, double y) {
    this->x(x);
    this->y(y);
}

void Point2D::x(double x) {
    this->_x = x;
}

void Point2D::y(double y) {
    this->_y = y;
}

double Point2D::x() const {
    return _x;
}

double Point2D::y() const {
    return _y;
}

double Point2D::distanceTo(const Point2D& other) const {
    double dx = _x - other._x;
    double dy = _y - other._y;
    return std::sqrt(dx * dx + dy * dy);
}

double Point2D::dotProduct(const Point2D& other) const {
    return x() * other.x() + y() * other.y();
}

bool Point2D::operator==(const Point2D& other) const {
    return _x == other._x && _y == other._y;
}

Point2D& Point2D::operator=(const Point2D& other) {
    x(other.x());
    y(other.y());
    return *this;
}

// Overloaded addition operator
const Point2D operator+(const Point2D& p1, const Point2D& p2) {
    return Point2D(p1._x + p2._x, p1._y + p2._y);
}

// Overloaded subtraction operator
const Point2D operator-(const Point2D& p1, const Point2D& p2) {
    return Point2D(p1._x - p2._x, p1._y - p2._y);
}

std::istream& operator>>(std::istream& is, Point2D& point) {
    double x, y;
    char comma;
    is >> x >> comma >> y;
    point.set(x, y);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Point2D& point) {
    os << '(' << point.x() << " , " << point.y() << ')';
    return os;
}