//#include "../include/myfigures.hpp"

template <class T>
Triangle<T>::Triangle() : a(0.0, 0.0), b(0.0, 0.0), c(0.0, 0.0),
                    sideA(0), sideB(0), sideC(0) {}

template <class T>
Triangle<T>::Triangle(const Triangle& other) {
    _copy(other);
}

template <class T>
void Triangle<T>::printVertices(std::ostream& os) const {
    os << "1st vertex: " << a << std::endl;
    os << "2nd vertex: " << b << std::endl;
    os << "3rd vertex: " << c << std::endl;
}

template <class T>
void Triangle<T>::readVertices(std::istream& is) {
    std::cout << "Enter first vertex coordinates (ex. '2.1 , 3.4'): ";
    is >> a;
    std::cout << "Enter second vertex coordinates: ";
    is >> b;
    std::cout << "Enter third vertex coordinates: ";
    is >> c;
    // Check if the entered coordinates form a valid triangle
    double lA = a.distanceTo(b);
    double lB = b.distanceTo(c);
    double lC = c.distanceTo(a);

    if (lA + lB <= lC || lB + lC <= lA || lC + lA <= lB) {
        std::cerr << "The entered coordinates do not form a valid triangle." << std::endl;
    }
}

template <class T>
Figure& Triangle<T>::_copy(const Figure& other) {
    const Triangle* otherTr = dynamic_cast<const Triangle*>(&other);
    if (otherTr) {
        a = otherTr->a;
        b = otherTr->b;
        c = otherTr->c;
    }
    return *this;
}

template <class T>
Figure& Triangle<T>::_move(Figure& other) {
    const Triangle* otherTr = dynamic_cast<const Triangle*>(&other);
    if (otherTr) {
        a = std::move(otherTr->a);
        b = std::move(otherTr->b);
        c = std::move(otherTr->c);
    }
    return *this;
}

template <class T>
Point2D<T> Triangle<T>::center() {
    T centerX = (a.x() + b.x() + c.x()) / 3.0;
    T centerY = (a.y() + b.y() + c.y()) / 3.0;
    return Point2D<T>(centerX, centerY);
} 


template <class T>
bool Triangle<T>::isSameAs(const Figure& other) const {
    const Triangle* otherTr = dynamic_cast<const Triangle*>(&other);
    if (otherTr){
        return (a == otherTr->a && b == otherTr->b 
             && c == otherTr->c);
    }
    return false;
}

template <class T>
double Triangle<T>::getArea() const {
    double lA = a.distanceTo(b);
    double lB = b.distanceTo(c);
    double lC = c.distanceTo(a);
    double semiP = (lA + lB + lC) / 2.0;
    // Формула Герона
    return sqrt(semiP * (semiP - lA) * (semiP - lB) * (semiP - lC));
}

// === RECTANGLE ===

template <class T>
Rectangle<T>::Rectangle() : a(0, 0), b(0, 0), c(0, 0), d(0, 0), sideA(0), sideB(0) {}

template <class T>
Rectangle<T>::Rectangle(const Rectangle<T>& other) {
    _copy(other);
}

template <class T>
void Rectangle<T>::printVertices(std::ostream& os) const {
    os << "1st vertex: " << a << std::endl;
    os << "2nd vertex: " << b << std::endl;
    os << "3rd vertex: " << c << std::endl;
    os << "4th vertex: " << d << std::endl;
}

template <class T>
void Rectangle<T>::readVertices(std::istream& is) {
    std::cout << "Enter 1st vertex coordinates (ex. '2.1 , 3.4'): ";
    is >> a;
    std::cout << "Enter 2nd vertex coordinates: ";
    is >> b;
    std::cout << "Enter 3rd vertex coordinates: ";
    is >> c;
    std::cout << "Enter 4th vertex coordinates: ";
    is >> d;
    //std::cout << sideA << " " << sideB << std::endl;
    // Check if the figure is a rectangle
    T lA = a.distanceTo(b);
    T lB = b.distanceTo(c);
    T lC = c.distanceTo(d);
    T lD = d.distanceTo(a);

    if (lA != lC || lB != lD) {
        std::cerr << "The entered coordinates do not form a rectangle." << std::endl;
    }
}

template <class T>
Figure& Rectangle<T>::_copy(const Figure& other) {
    const Rectangle<T>* otherRect = dynamic_cast<const Rectangle<T>*>(&other);
    if (otherRect) {
        a = otherRect->a;
        b = otherRect->b;
        c = otherRect->c;
        d = otherRect->d;
    }
    return *this;
}

template <class T>
Figure& Rectangle<T>::_move(Figure& other) {
    const Rectangle<T>* otherRect = dynamic_cast<const Rectangle<T>*>(&other);
    if (otherRect) {
        a = std::move(otherRect->a);
        b = std::move(otherRect->b);
        c = std::move(otherRect->c);
        d = std::move(otherRect->d);
    }
    return *this;
}

template <class T>
Point2D<T> Rectangle<T>::center() {
    T centerX = (a.x() + c.x()) / 2.0;
    T centerY = (a.y() + c.y()) / 2.0;
    return Point2D<T>(centerX, centerY);
}

template <class T>
bool Rectangle<T>::isSameAs(const Figure& other) const {
    const Rectangle<T>* otherRect = dynamic_cast<const Rectangle<T>*>(&other);
    if (otherRect){
        return (a == otherRect->a && b == otherRect->b 
             && c == otherRect->c && d == otherRect->d);
    }
    return false;
}

template <class T>
double Rectangle<T>::getArea() const {
    double lA = a.distanceTo(b);
    double lB = b.distanceTo(c);
    return lA * lB;
}

// === SQUARE ===

template <class T>
Square<T>::Square() : Rectangle<T>() {};

template <class T>
void Square<T>::readVertices(std::istream& is) {
    std::cout << "Enter 1st vertex coordinates (ex. '2.1 , 3.4'): ";
    is >> this->a;
    std::cout << "Enter 2nd vertex coordinates: ";
    is >> this->b;
    std::cout << "Enter 3rd vertex coordinates: ";
    is >> this->c;
    std::cout << "Enter 4th vertex coordinates: ";
    is >> this->d;
    // Check if the figure is a rectangle
    double lA = this->a.distanceTo(this->b);
    double lB = this->b.distanceTo(this->c);
    double lC = this->c.distanceTo(this->d);
    double lD = this->d.distanceTo(this->a);

    if (lA != lC || lB != lD) {
        std::cerr << "The entered coordinates do not form a rectangle." << std::endl;
    } else if (lA != lB || lB != lC || lC != lD) {
        std::cerr << "The entered coordinates do not form a square." << std::endl;
    }
}
