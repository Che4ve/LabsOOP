//#include "../include/point2D.hpp"

template <class T>
Point2D<T>::Point2D(Point2D&& other) noexcept {
    _x = std::move(other._x);
    _y = std::move(other._y);
}

template <class T>
void Point2D<T>::set(T x, T y) {
    this->x(x);
    this->y(y);
}

template <class T>
void Point2D<T>::x(T x) {
    this->_x = x;
}

template <class T>
void Point2D<T>::y(T y) {
    this->_y = y;
}

template <class T>
T Point2D<T>::x() const {
    return _x;
}

template <class T>
T Point2D<T>::y() const {
    return _y;
}

template <class T>
T Point2D<T>::distanceTo(const Point2D& other) const {
    T dx = _x - other._x;
    T dy = _y - other._y;
    return std::sqrt(dx * dx + dy * dy);
}

template <class T>
T Point2D<T>::dotProduct(const Point2D& other) const {
    return x() * other.x() + y() * other.y();
}

template <class T>
bool Point2D<T>::operator==(const Point2D& other) const {
    return _x == other._x && _y == other._y;
}

template <class T>
Point2D<T>& Point2D<T>::operator=(const Point2D& other) {
    x(other.x());
    y(other.y());
    return *this;
}


// Overloaded addition operator
// template <class T>
// const Point2D<T> operator+(const Point2D<T>& p1, const Point2D<T>& p2) {
//     return Point2D<T>(p1._x + p2._x, p1._y + p2._y);
// }

// // Overloaded subtraction operator
// template <class T>
// const Point2D<T> operator-(const Point2D<T>& p1, const Point2D<T>& p2) {
//     return Point2D<T>(p1._x - p2._x, p1._y - p2._y);
// }

// template <class T = double>
// std::istream& operator>>(std::istream& is, Point2D<T>& point) {
//     double x, y;
//     char comma;
//     is >> x >> comma >> y;
//     point.set(x, y);
//     return is;
// }

// template <class T>
// std::ostream& operator<<(std::ostream& os, const Point2D<T>& point) {
//     os << '(' << point.x() << " , " << point.y() << ')';
//     return os;
// }