// Чесноков В.Д. | Вариант 25
// 25.   Треугольник,  Квадрат,  Прямоугольник
#include <iostream>
#include "./include/point2D.h"
#include "./include/myfigures.h"
#include "./include/vector.h"

int main(int argc, char** argv) {
    Triangle tr;

    std::cin >> tr;

    std::cout << tr;

    std::cout << tr.center() << std::endl;

    std::cout << "TRIANGLE----------------------------" << std::endl;

    tr.a = Point2D(1, 1);
    tr.b = Point2D(3.5, 5);
    tr.c = Point2D(1.5, 0);
    std::cout << tr.center() << std::endl;
    std::cout << double(tr) << std::endl;

    Rectangle rect;

    rect.a = Point2D(0, 0);
    rect.b = Point2D(0, 3);
    rect.c = Point2D(1, 3);
    rect.d = Point2D(1, 0);

    //std::cin >> rect;

    //std::cout << rect;
    std::cout << "RECT--------------------------------" << std::endl;
    std::cout << rect.center() << std::endl;
    std::cout << double(rect) << std::endl;
    
    std::cout << "SUM---------------------------------" << std::endl;

    Triangle tr2 = tr;

    Vector<Figure*> figures;

    figures.push_back(&rect);
    figures.push_back(&tr);
    figures.push_back(&tr2);

    double totalArea = 0.0;

    for (const auto& figure : figures) {
        totalArea += double(*figure);
        std::cout << double(*figure) << "\n +" << std::endl;
    }

    std::cout << "Total Area: " << totalArea << std::endl;

    return 0;
}
