#include "../include/myfigures.h"

Triangle::Triangle() : a(0,0), b(0,0), c(0,0),
                    sideA(0), sideB(0), sideC(0) {}

Triangle::Triangle(const Triangle& other) {
    _copy(other);
}

void Triangle::printVertices(std::ostream& os) const {
    os << "1st vertex: " << a << std::endl;
    os << "2nd vertex: " << b << std::endl;
    os << "3rd vertex: " << c << std::endl;
}

void Triangle::readVertices(std::istream& is) {
    std::cout << "Enter first vertex coordinates (ex. '2.1 , 3.4'): ";
    is >> a;
    std::cout << "Enter second vertex coordinates: ";
    is >> b;
    std::cout << "Enter third vertex coordinates: ";
    is >> c;
}


Figure& Triangle::_copy(const Figure& other) {
    const Triangle* otherTr = dynamic_cast<const Triangle*>(&other);
    if (otherTr) {
        a = otherTr->a;
        b = otherTr->b;
        c = otherTr->c;
    }
    return *this;
}

Figure& Triangle::_move(Figure& other) {
    const Triangle* otherTr = dynamic_cast<const Triangle*>(&other);
    if (otherTr) {
        a = std::move(otherTr->a);
        b = std::move(otherTr->b);
        c = std::move(otherTr->c);
    }
    return *this;
}

Point2D Triangle::center() {
    double centerX = (a.x() + b.x() + c.x()) / 3.0;
    double centerY = (a.y() + b.y() + c.y()) / 3.0;
    return Point2D(centerX, centerY);
} 


bool Triangle::isSameAs(const Figure& other) const {
    const Triangle* otherTr = dynamic_cast<const Triangle*>(&other);
    if (otherTr){
        return (a == otherTr->a && b == otherTr->b 
             && c == otherTr->c);
    }
    return false;
}

double Triangle::getArea() const {
    double lA = a.distanceTo(b);
    double lB = a.distanceTo(b);
    double lC = b.distanceTo(c);
    double semiP = (lA + lB + lC) / 2.0;
    // Формула Герона
    return sqrt(semiP * (semiP - lA) * (semiP - lB) * (semiP - lC));
}

// === RECTANGLE ===

Rectangle::Rectangle() : a(0,0), b(0,0), c(0,0), d(0,0),
                            sideA(0), sideB(0) {}

Rectangle::Rectangle(const Rectangle& other) {
    _copy(other);
}

void Rectangle::printVertices(std::ostream& os) const {
    os << "1st vertex: " << a << std::endl;
    os << "2nd vertex: " << b << std::endl;
    os << "3rd vertex: " << c << std::endl;
    os << "4rd vertex: " << d << std::endl;
}

void Rectangle::readVertices(std::istream& is) {
    std::cout << "Enter 1st vertex coordinates (ex. '2.1 , 3.4'): ";
    is >> a;
    std::cout << "Enter 2nd vertex coordinates: ";
    is >> b;
    std::cout << "Enter 3rd vertex coordinates: ";
    is >> c;
    std::cout << "Enter 4th vertex coordinates: ";
    is >> d;
    std::cout << sideA << " " << sideB << std::endl;

    //TODO: check for a rectangle
}

Figure& Rectangle::_copy(const Figure& other) {
    const Rectangle* otherRect = dynamic_cast<const Rectangle*>(&other);
    if (otherRect) {
        a = otherRect->a;
        b = otherRect->b;
        c = otherRect->c;
        d = otherRect->d;
    }
    return *this;
}

Figure& Rectangle::_move(Figure& other) {
    const Rectangle* otherRect = dynamic_cast<const Rectangle*>(&other);
    if (otherRect) {
        a = std::move(otherRect->a);
        b = std::move(otherRect->b);
        c = std::move(otherRect->c);
        d = std::move(otherRect->d);
    }
    return *this;
}

Point2D Rectangle::center() {
    double centerX = (a.x() + c.x()) / 2.0;
    double centerY = (a.y() + c.y()) / 2.0;
    return Point2D(centerX, centerY);
}

bool Rectangle::isSameAs(const Figure& other) const {
    const Rectangle* otherRect = dynamic_cast<const Rectangle*>(&other);
    if (otherRect){
        return (a == otherRect->a && b == otherRect->b 
             && c == otherRect->c && d == otherRect->d);
    }
    return false;
}

double Rectangle::getArea() const {
    double lA = a.distanceTo(b);
    double lB = b.distanceTo(c);
    return lA * lB;
}

// === SQUARE ===

Square::Square() : Rectangle() {};

