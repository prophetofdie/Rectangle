#pragma once
#include "Point.hpp"
#include <ostream>
#include <stdexcept> // for std::invalid_argument

template<typename Type>
class Rect {
	static_assert(std::is_arithmetic_v<Type>, "Type must be arithmetic");

	static Type min(Type f, Type s) {
		return f < s ? f : s;
	}
	static Type max(Type f, Type s) {
		return f > s ? f : s;
	}
public:
	Type width, height;
	Point<Type> origin; // Left lower point

	/// <summary>
	/// Initializes the rectangle from the bottom-left corner
	/// </summary>
	Rect(Point<Type> p, Type width, Type height)
		: origin{ p }, width{ width }, height{ height }
	{
		if (width < 0 || height < 0) 
			throw std::invalid_argument("Width and height must be non-negative.");
	}

	/// <summary>
	/// Initializes the rectangle from the bottom-left corner
	/// </summary>
	Rect(Type x, Type y, Type width, Type height)
		: Rect(Point<Type>(x, y), width, height)
	{ }

	/// <summary>
	/// Initializes the rectangle that encompasses both points
	/// </summary>
	Rect(Point<Type> first, Point<Type> second)
		: Rect(Point<Type>(min(first.x, second.x), min(first.y, second.y)),
			max(first.x, second.x) - min(first.x, second.x),
			max(first.y, second.y) - min(first.y, second.y))
	{ }

	/// <summary>
	/// Default constructor
	/// </summary>
	Rect() : Rect(0, 0, 0, 0)
	{ }

	/// <summary>
	/// Assignment operator: Copies the data from another rectangle to the current one
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	Rect<Type>& operator=(const Rect<Type>& other) {
		this->origin = other.origin;
		this->height = other.height;
		this->width = other.width;
		return *this;
	}

	/// <summary>
	/// Equality operator: Checks if two rectangles are equal by comparing their origin, width, and height
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	bool operator==(const Rect<Type>& other) const {
		return this->origin.x == other.origin.x && this->origin.y == other.origin.y &&
			this->width == other.width && this->height == other.height;
	}
	
	/// <summary>
	/// Inequality operator: Checks if two rectangles are not equal by comparing their origin, width, and height
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	bool operator!=(const Rect<Type>& other) const {
		return !operator==(other);
	}

	/// <summary>
	/// Returns the Y-coordinate of the bottom side of the rectangle
	/// </summary>
	Type Bottom() const {
		return this->origin.y;
	}

	/// <summary>
	/// Returns the X-coordinate of the left side of the rectangle
	/// </summary>
	Type Left() const {
		return this->origin.x;
	}

	/// <summary>
	/// Returns the X-coordinate of the right side of the rectangle
	/// </summary>
	Type Right() const {
		return this->origin.x + width;
	}

	/// <summary>
	/// Returns the Y-coordinate of the top side of the rectangle
	/// </summary>
	Type Top() const {
		return this->origin.y + height;
	}

	/// <summary>
	/// Indicates whether the rectangle contains the given point
	/// </summary>
	bool Contains(const Point<Type>& p) const {
		return p.x >= Left() && p.x <= Right() && p.y >= Bottom() && p.y <= Top();
	}

	/// <summary>
	/// Indicates whether the rectangle contains the given rectangle
	/// </summary>
	bool Contains(const Rect<Type>& r) const {
		return r.Left() >= Left() && r.Right() <= Right() && r.Bottom() >= Bottom() && r.Top() <= Top();
	}

	/// <summary>
	/// Returns the intersection of the rectangles  
	/// </summary>
	Rect<Type> Intersect(const Rect<Type>& other) const {
		Type left = max(Left(), other.Left());
		Type bottom = max(Bottom(), other.Bottom());
		Type right = min(Right(), other.Right());
		Type top = min(Top(), other.Top());

		if (right < left || top < bottom) {
			// No intersection, return an empty rectangle
			return Rect<Type>();
		}
		return Rect<Type>(Point<Type>(left, bottom), right - left, top - bottom);
	}

	/// <summary>
	/// Returns a rectangle expanded enough to include the new rectangle
	/// </summary>
	Rect<Type> Union(const Rect<Type>& other) const {
		return Rect<Type>(
			Point<Type>(min(origin.x, other.origin.x), min(origin.y, other.origin.y)),
			max(origin.x + width, other.origin.x + other.width) - min(origin.x, other.origin.x),
			max(origin.y + height, other.origin.y + other.height) - min(origin.y, other.origin.y)
		);
	}

	/// <summary>
	/// Returns a rectangle expanded enough to include the new point
	/// </summary>
	Rect<Type> Union(const Point<Type>& other) const {
		return Rect<Type>(
			Point<Type>(min(origin.x, other.x), min(origin.y, other.y)),
			max(origin.x + width, other.x) - min(origin.x, other.x),
			max(origin.y + height, other.y) - min(origin.y, other.y)
		);
	}

	/// <summary>
	/// Moving a rectangle to a given point
	/// </summary>
	void Move(const Point<Type>& movement) {
		this->origin.x += movement.x;
		this->origin.y += movement.y;
	}

	/// <summary>
	/// Returns the area of the rectangle
	/// </summary>
	Type Area() const {
		return width * height;
	}

	/// <summary>
	/// Returns the perimeter of the rectangle
	/// </summary>
	Type Perimeter() const {
		return 2 * (width + height);
	}
};

/// <summary>
/// Overloading the output stream operator
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="os"></param>
/// <param name="rect"></param>
/// <returns></returns>
template<typename T>
std::ostream& operator<<(std::ostream& os, const Rect<T>& rect) {
	os << "Rectangle: [Origin: (" << rect.origin.x << ", " << rect.origin.y
		<< "), Width: " << rect.width << ", Height: " << rect.height << "]";
	return os;
}