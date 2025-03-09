#include <iostream>
#include "Rectangle.hpp"

template<typename T>
void Info(Rect<T> r) {
    std::cout << "LeftBottom ";
    std::cout << r.Left() << ' ';
    std::cout << r.Bottom() << '\n';
    std::cout << "RightTop ";
    std::cout << r.Right() << ' ';
    std::cout << r.Top() << '\n';
    std::cout << "Area " << r.Area() << '\n';
    std::cout << "Width " << r.width << '\n';
    std::cout << "Height " << r.height << '\n';

    std::cout << '\n';
}

int main()
{
    Rect<int> r(20, 10, 10, 5);
    Info(r);

    Rect<int> r1(-20, 10, 10, 5);
    Info(r1);

    auto r2 = r1.Union(r);
    Info(r2);

    std::cout << r2.Contains(r1) << '\n';
    std::cout << r2.Contains(r) << '\n';

    std::cout << "Hello World!\n";
}