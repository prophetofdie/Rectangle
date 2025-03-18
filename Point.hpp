#pragma once

template<typename T>
struct Point {
	static_assert(std::is_arithmetic_v<T>, "Type must be arithmetic");

	T x, y;
	Point(T x, T y)
		: x{ x }, y{ y }
	{}
	Point()
		: x{ 0 }, y{ 0 }
	{}
};