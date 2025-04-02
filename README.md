# Rect Template Class

This project implements a `Rect` (Rectangle) class template in C++ that allows for manipulation and querying of 2D rectangles with arbitrary numeric types. The class is designed to be used with types that support comparison and arithmetic operations, such as integers and floating-point numbers. Minimum required version Ñ++14

## Features

- Supports any numeric type (`int`, `float`, `double`, etc.).
- Represents a rectangle defined by its lower-left corner (`origin`), width, and height.
- Provides functionality for geometric operations such as area, perimeter, containment checks, intersections, and unions.

## Installation

```sh
git clone https://github.com/prophetofdie/Rectangle
```

```sh
cmake -DCMAKE_BUILD_TYPE=Release ../Rectangle/CMakeLists.txt
```

```sh
cmake --build ../Rectangle
```

## Contents

- **Rect Class**: The main class representing the rectangle.
- **Point Class**: A simple structure used to represent 2D points, defining the position of the rectangle's origin (the bottom-left corner).

## Class Overview

### Constructor Overloading

The `Rect` class provides several constructors for flexibility in how the rectangle is created:

- **Rect(Point<Type> p, Type width, Type height)**: Initializes the rectangle from a point (the lower-left corner) and the width and height.
- **Rect(Type x, Type y, Type width, Type height)**: Initializes the rectangle using coordinates for the lower-left corner and the width and height.
- **Rect(Point<Type> first, Point<Type> second)**: Initializes the rectangle based on two points, which define the opposite corners of the rectangle.
- **Rect()**: Default constructor, creates an empty rectangle with a width and height of zero.

### Member Functions

- **Bottom()**: Returns the y-coordinate of the rectangle's bottom edge.
- **Left()**: Returns the x-coordinate of the rectangle's left edge.
- **Right()**: Returns the x-coordinate of the rectangle's right edge.
- **Top()**: Returns the y-coordinate of the rectangle's top edge.
- **Contains(Point<Type> p)**: Checks if the given point is inside the rectangle.
- **Contains(Rect<Type> r)**: Checks if the given rectangle is entirely contained within the current rectangle.
- **Intersect(Rect<Type> other)**: Returns the intersection of the current rectangle and another rectangle, or an empty rectangle if they do not intersect.
- **Union(Rect<Type> other)**: Returns the smallest rectangle that contains both the current rectangle and the given one.
- **Union(Point<Type> other)**: Returns the smallest rectangle that contains both the current rectangle and the given point.
- **Move(Point<Type> movement)**: Moves the rectangle by a specified point, effectively translating it.
- **Area()**: Returns the area of the rectangle.
- **Perimeter()**: Returns the perimeter of the rectangle.

### Comparison Operators

- **operator==**: Compares two rectangles for equality.
- **operator!=**: Compares two rectangles for inequality.

### Error Handling

- If the width or height of the rectangle is negative when it is initialized, an `std::invalid_argument` exception is thrown.

## Example Usage

```cpp
#include "Rect.hpp"
#include <iostream>

int main() {
    Point<int> p1(0, 0);
    Rect<int> rect1(p1, 4, 3);
    Rect<int> rect2(1, 1, 2, 2);

    std::cout << "Area of rect1: " << rect1.Area() << std::endl;
    std::cout << "Perimeter of rect1: " << rect1.Perimeter() << std::endl;

    // Check if a point is inside rect1
    Point<int> p2(2, 2);
    std::cout << "Does rect1 contain point (2, 2)? " << (rect1.Contains(p2) ? "Yes" : "No") << std::endl;

    // Check intersection of rect1 and rect2
    Rect<int> intersection = rect1.Intersect(rect2);
    std::cout << "Area of intersection: " << intersection.Area() << std::endl;

    // Move rect1 by (1, 1)
    rect1.Move(Point<int>(1, 1));
    std::cout << "New origin of rect1: (" << rect1.origin.x << ", " << rect1.origin.y << ")" << std::endl;

    return 0;
}

## User Interface

- **Working with Rectangles**: Create, modify, and manipulate rectangles.
- **File Loading and Saving**: Load and save variables with rectangles to/from files.
- **Variable Management**: Create new variables, modify them, or view existing ones.

## Functions

### Main Menu

In the main menu, the user can select one of the following options:

1. **Show Existing Variables**: Display a list of all created variables and their values.
2. **Create a New Variable**: Create a new variable representing a rectangle. You can choose the method of creation: default, by specifying coordinates, merging, or intersecting two other rectangles.
3. **Modify a Variable**: Modify an existing rectangle's parameters (coordinates, width, height, and other properties).
4. **Load Variables from File**: Load variables and their values from a file.
5. **Save Variables to File**: Save all variables to a file.
6. **Exit**: Exit the program.

### Creating a Variable

When creating a new variable, the user is offered the following options:

- **Create a Rectangle by Default**.
- **Create a Rectangle with Specified Parameters**: coordinates, width, and height.
- **Create a Rectangle by Merging Two Existing Rectangles**.
- **Create a Rectangle by Intersecting Two Existing Rectangles**.

### Modifying a Variable

After selecting an existing rectangle to modify, the user is given the following options:

- Show the area of the rectangle.
- Show the perimeter of the rectangle.
- Change the X coordinate.
- Change the Y coordinate.
- Change the width.
- Change the height.

### File Operations

The program allows loading and saving data to files. When loading from a file, if there are name collisions, existing variables will be overwritten.

Only valid file names are accepted, and the program supports text files for input/output.

### Input Validation and Checks

- **Variable Name Validation**: A variable name must not contain invalid characters (such as spaces, digits, or special symbols).
- **Number Input Validation**: The program checks that input values are valid and match the expected format (e.g., numbers with a decimal point).
- **File Name Validation**: The file name must be valid and not contain special characters.

