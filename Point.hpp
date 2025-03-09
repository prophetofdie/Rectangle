#pragma once

// Концепт для числовых типов
template <typename T>
concept Numeric = std::is_arithmetic_v<T>;  // Проверка на числовой тип (int, float, double и т.д.)

template<Numeric T>
struct Point {
	T x, y;
	Point(T x, T y)
		: x{ x }, y{ y }
	{}
	Point()
		: x{ 0 }, y{ 0 }
	{}
};