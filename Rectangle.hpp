#include "Point.hpp"
#include <stdexcept> // ��� std::invalid_argument

template<typename Type>
class Rect {
	static Type min(Type f, Type s) {
		return f < s ? f : s;
	}
	static Type max(Type f, Type s) {
		return f > s ? f : s;
	}
public:
	Type width, height;
	Point<Type> origin;

	/// <summary>
	/// �������������� �������������, � ������ ������� ����
	/// </summary>
	Rect(Point<Type> p, Type width, Type height)
		: origin{ p }, width{ width }, height{ height }
	{
		if (width < 0 || height < 0) throw std::invalid_argument("Width and height must be non-negative.");
	}

	/// <summary>
	/// �������������� �������������, � ������ ������� ����
	/// </summary>
	Rect(Type x, Type y, Type width, Type height)
		: Rect(Point<Type>(x, y), width, height)
	{ }

	/// <summary>
	/// �������������� �������������, ��������� ��� �����
	/// </summary>
	Rect(Point<Type> first, Point<Type> second)
		: Rect(Point<Type>(min(first.x, second.x), min(first.y, second.y)),
			max(first.x, second.x) - min(first.x, second.x),
			max(first.y, second.y) - min(first.y, second.y))
	{ }

	Rect() : Rect(0, 0, 0, 0)
	{ }

	/// <summary>
	/// ���������� ���������� �� ��� Y ������ ������� ��������������
	/// </summary>
	Type Bottom() const {
		return this->origin.y;
	}

	/// <summary>
	/// ���������� ���������� �� ��� X ����� ������� ��������������
	/// </summary>
	Type Left() const {
		return this->origin.x;
	}

	/// <summary>
	/// ���������� ���������� �� ��� X ������ ������� ��������������
	/// </summary>
	Type Right() const {
		return this->origin.x + width;
	}

	/// <summary>
	/// ���������� ���������� �� ��� Y ������� ������� ��������������
	/// </summary>
	Type Top() const {
		return this->origin.y + height;
	}

	bool operator==(const Rect<Type>& other) const {
		return this->origin.x == other.origin.x && this->origin.y == other.origin.y &&
			this->width == other.width && this->height == other.height;
	}

	bool operator!=(const Rect<Type>& other) const {
		return !operator==(other);
	}

	/// <summary>
	/// ��������� �������� �� ������������� ������ �����
	/// </summary>
	bool Contains(const Point<Type>& p) const {
		return p.x >= Left() && p.x <= Right() && p.y >= Bottom() && p.y <= Top();
	}

	/// <summary>
	/// ��������� �������� �� ������������� ������ �������������
	/// </summary>
	bool Contains(const Rect<Type>& r) const {
		return r.Left() >= Left() && r.Right() <= Right() && r.Bottom() >= Bottom() && r.Top() <= Top();
	}

	/// <summary>
	/// ���������� ����������� ���������������  
	/// </summary>
	Rect<Type> Intersect(const Rect<Type>& other) const {
		Type left = max(Left(), other.Left());
		Type bottom = max(Bottom(), other.Bottom());
		Type right = min(Right(), other.Right());
		Type top = min(Top(), other.Top());

		if (right < left || top < bottom) {
			// ��� �����������, ���������� ������ �������������
			return Rect<Type>();
		}
		return Rect<Type>(Point<Type>(left, bottom), right - left, top - bottom);
	}

	/// <summary>
	/// ���������� �������������, ����������� �� ������,
	/// ����������� ��� �� �������� ����� �������������
	/// </summary>
	Rect<Type> Union(const Rect<Type>& other) const {
		return Rect<Type>(
			Point<Type>(min(origin.x, other.origin.x), min(origin.y, other.origin.y)),
			max(origin.x + width, other.origin.x + other.width) - min(origin.x, other.origin.x),
			max(origin.y + height, other.origin.y + other.height) - min(origin.y, other.origin.y)
		);
	}

	/// <summary>
	/// ���������� �������������, ����������� �� ������,
	/// ����������� ��� �� �������� ����� �����
	/// </summary>
	Rect<Type> Union(const Point<Type>& other) const {
		return Rect<Type>(
			Point<Type>(min(origin.x, other.x), min(origin.y, other.y)),
			max(origin.x + width, other.x) - min(origin.x, other.x),
			max(origin.y + height, other.y) - min(origin.y, other.y)
		);
	}

	/// <summary>
	/// ���������� ������� ��������������
	/// </summary>
	Type Area() const {
		return width * height;
	}

	/// <summary>
	/// ���������� �������� ��������������
	/// </summary>
	Type Perimeter() const {
		return 2 * (width + height);
	}
};
