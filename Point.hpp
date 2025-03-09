#pragma once

// ������� ��� �������� �����
template <typename T>
concept Numeric = std::is_arithmetic_v<T>;  // �������� �� �������� ��� (int, float, double � �.�.)

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