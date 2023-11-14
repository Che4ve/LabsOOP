// Чесноков В.Д. | Вариант 25
// 25.   Треугольник,  Квадрат,  Прямоугольник
#include <iostream>
#include "./include/point2D.hpp"
#include "./include/myfigures.hpp"
#include "./include/vector.hpp"

int main(int argc, char** argv) {
    Triangle<double> tr;
    
    std::cout << tr.center() << std::endl;

    std::cout << "TRIANGLE----------------------------" << std::endl;

    tr.a = Point2D<double>(1, 1);
    tr.b = Point2D<double>(3.5, 5);
    tr.c = Point2D<double>(1.5, 0);
    std::cout << tr.center() << std::endl;
    std::cout << double(tr) << std::endl;

    Rectangle<double> rect;

    rect.a = Point2D<double>(0.0, 0.0);
    rect.b = Point2D<double>(0.0, 3.0);
    rect.c = Point2D<double>(1.0, 3.0);
    rect.d = Point2D<double>(1.0, 0.0);

    std::cout << "RECT--------------------------------" << std::endl;
    std::cout << rect.center() << std::endl;
    std::cout << double(rect) << std::endl;
    
    std::cout << "SUM---------------------------------" << std::endl;

    Triangle<double> tr2{ tr };

    Vector< std::shared_ptr<Figure> > figures;

    figures.push_back(std::make_shared<Rectangle<double>>(rect));
    figures.push_back(std::make_shared<Triangle<double>>(tr));
    figures.push_back(std::make_shared<Triangle<double>>(tr2));

    double totalArea = 0.0;

    for (const auto& figure : figures) {
        totalArea += double(*figure);
        std::cout << double(*figure) << "\n +" << std::endl;
    }

    std::cout << "Total Area: " << totalArea << std::endl;

    return 0;
}
