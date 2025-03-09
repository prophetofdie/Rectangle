#include <iostream>
#include "Rectangle.hpp"
#include "Point.hpp"
#include <cassert>  // Для использования assert

void testDefaultConstructor() {
    Rect<int> r;
    assert(r.width == 0 && r.height == 0);
    assert(r.origin.x == 0 && r.origin.y == 0);
    std::cout << "testDefaultConstructor passed." << std::endl;
}

void testPointConstructor() {
    Point<int> p(2, 3);
    Rect<int> r(p, 5, 7);
    assert(r.origin.x == 2 && r.origin.y == 3);
    assert(r.width == 5 && r.height == 7);
    std::cout << "testPointConstructor passed." << std::endl;
}

void testXYConstructor() {
    Rect<int> r(1, 2, 4, 5);
    assert(r.origin.x == 1 && r.origin.y == 2);
    assert(r.width == 4 && r.height == 5);
    std::cout << "testXYConstructor passed." << std::endl;
}

void testTwoPointConstructor() {
    Point<int> p1(1, 2), p2(4, 5);
    Rect<int> r(p1, p2);
    assert(r.origin.x == 1 && r.origin.y == 2);
    assert(r.width == 3 && r.height == 3);
    std::cout << "testTwoPointConstructor passed." << std::endl;
}

void testIntersection() {
    Rect<int> r1(0, 0, 5, 5);
    Rect<int> r2(3, 3, 5, 5);
    Rect<int> intersection = r1.Intersect(r2);
    assert(intersection.origin.x == 3 && intersection.origin.y == 3);
    assert(intersection.width == 2 && intersection.height == 2);
    std::cout << "testIntersection passed." << std::endl;
}

void testNoIntersection() {
    Rect<int> r1(0, 0, 2, 2);
    Rect<int> r2(3, 3, 2, 2);
    Rect<int> intersection = r1.Intersect(r2);
    assert(intersection.width == 0 && intersection.height == 0);
    std::cout << "testNoIntersection passed." << std::endl;
}

void testUnion() {
    Rect<int> r1(0, 0, 3, 3);
    Rect<int> r2(2, 2, 4, 4);
    Rect<int> unionRect = r1.Union(r2);
    assert(unionRect.origin.x == 0 && unionRect.origin.y == 0);
    assert(unionRect.width == 6 && unionRect.height == 6);
    std::cout << "testUnion passed." << std::endl;
}

void testMove() {
    Rect<int> r(0, 0, 3, 3);
    Point<int> movement(2, 3);
    r.Move(movement);
    assert(r.origin.x == 2 && r.origin.y == 3);
    std::cout << "testMove passed." << std::endl;
}

void testArea() {
    Rect<int> r(0, 0, 5, 10);
    assert(r.Area() == 50);
    std::cout << "testArea passed." << std::endl;
}

void testPerimeter() {
    Rect<int> r(0, 0, 5, 10);
    assert(r.Perimeter() == 30);
    std::cout << "testPerimeter passed." << std::endl;
}

void testContainsPoint() {
    Rect<int> r(0, 0, 5, 5);
    Point<int> p(2, 2);
    assert(r.Contains(p) == true);

    Point<int> p2(6, 6);
    assert(r.Contains(p2) == false);
    std::cout << "testContainsPoint passed." << std::endl;
}

void testContainsRect() {
    Rect<int> r1(0, 0, 5, 5);
    Rect<int> r2(1, 1, 3, 3);
    assert(r1.Contains(r2) == true);

    Rect<int> r3(4, 4, 2, 2);
    assert(r1.Contains(r3) == false);
    std::cout << "testContainsRect passed." << std::endl;
}

void testEquality() {
    Rect<int> r1(0, 0, 5, 5);
    Rect<int> r2(0, 0, 5, 5);
    assert(r1 == r2);

    Rect<int> r3(1, 1, 5, 5);
    assert(r1 != r3);
    std::cout << "testEquality passed." << std::endl;
}

void testDoubleType() {
    Rect<double> r(0.5, 1.5, 3.0, 4.0);
    assert(r.origin.x == 0.5 && r.origin.y == 1.5);
    assert(r.width == 3.0 && r.height == 4.0);
    std::cout << "testDoubleType passed." << std::endl;
}

void testNegativeCoordinates() {
    Rect<int> r(-2, -3, 5, 6);
    assert(r.origin.x == -2 && r.origin.y == -3);
    assert(r.width == 5 && r.height == 6);
    std::cout << "testNegativeCoordinates passed." << std::endl;
}

void testNegativeWidthHeight() {
    try {
        Rect<int> r(0, 0, -5, 5);
        std::cerr << "testNegativeWidthHeight failed: exception not thrown." << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "testNegativeWidthHeight passed: " << e.what() << std::endl;
    }

    try {
        Rect<int> r(0, 0, 5, -5);
        std::cerr << "testNegativeWidthHeight failed: exception not thrown." << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "testNegativeWidthHeight passed: " << e.what() << std::endl;
    }
}

void testNegativeMovement() {
    Rect<int> r(0, 0, 5, 5);
    Point<int> movement(-3, -3);
    r.Move(movement);
    assert(r.origin.x == -3 && r.origin.y == -3);
    std::cout << "testNegativeMovement passed." << std::endl;
}

void testNegativeIntersection() {
    Rect<int> r1(-5, -5, 5, 5);
    Rect<int> r2(-3, -3, 5, 5);
    Rect<int> intersection = r1.Intersect(r2);
    assert(intersection.origin.x == -3 && intersection.origin.y == -3);
    assert(intersection.width == 3 && intersection.height == 3);
    std::cout << "testNegativeIntersection passed." << std::endl;
}

void testDoubleIntersection() {
    Rect<double> r1(0.5, 0.5, 2.5, 3.5);
    Rect<double> r2(1.0, 1.0, 2.5, 3.5);
    Rect<double> intersection = r1.Intersect(r2);
    assert(intersection.origin.x == 1.0 && intersection.origin.y == 1.0);
    assert(intersection.width == 2.0 && intersection.height == 3.0);
    std::cout << "testDoubleIntersection passed." << std::endl;
}

void testDoubleUnion() {
    Rect<double> r1(0.5, 0.5, 3.0, 4.0);
    Rect<double> r2(2.0, 2.0, 5.0, 6.0);
    Rect<double> unionRect = r1.Union(r2);
    assert(unionRect.origin.x == 0.5 && unionRect.origin.y == 0.5);
    assert(unionRect.width == 6.5 && unionRect.height == 7.5);
    std::cout << "testDoubleUnion passed." << std::endl;
}

void testContainsNegativePoint() {
    Rect<int> r(-5, -5, 5, 5);
    Point<int> p(-3, -3);
    assert(r.Contains(p) == true);

    Point<int> p2(-6, -6);
    assert(r.Contains(p2) == false);
    std::cout << "testContainsNegativePoint passed." << std::endl;
}

void testDoubleArea() {
    Rect<double> r(1.5, 2.5, 4.5, 5.5);
    assert(r.Area() == 4.5 * 5.5);
    std::cout << "testDoubleArea passed." << std::endl;
}

void testDoublePerimeter() {
    Rect<double> r(1.5, 2.5, 4.5, 5.5);
    assert(r.Perimeter() == 2 * (4.5 + 5.5));
    std::cout << "testDoublePerimeter passed." << std::endl;
}

void testDoubleMove() {
    Rect<double> r(0.5, 0.5, 3.0, 4.0);
    Point<double> movement(2.5, 3.5);
    r.Move(movement);
    assert(r.origin.x == 3.0 && r.origin.y == 4.0);
    std::cout << "testDoubleMove passed." << std::endl;
}

int main() {
    // Тесты для типа int 
    // Положительные значения
    testDefaultConstructor();
    testPointConstructor();
    testXYConstructor();
    testTwoPointConstructor();
    testIntersection();
    testNoIntersection();
    testUnion();
    testMove();
    testArea();
    testPerimeter();
    testContainsPoint();
    testContainsRect();
    testEquality();
    // Тесты для типа double
    testDoubleType();
    testDoubleIntersection();
    testDoubleUnion();
    testDoubleArea();
    testDoublePerimeter();
    testDoubleMove();

    // Тесты для отрицательных значений
    testNegativeCoordinates();
    testNegativeWidthHeight();
    testNegativeMovement();
    testNegativeIntersection();
    testContainsNegativePoint();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
