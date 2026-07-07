#include "Vector2.h"

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float _x, float _y)
{
	x = _x;
	y = _y;
}

Vector2::Vector2(const Vector2& other)
{
	x = other.x;
	y = other.y;
}

Vector2& Vector2::operator=(const Vector2& other)
{
	if (this != &other)
	{
		x = other.x;
		y = other.y;
	}

	return *this;
}

Vector2& Vector2::operator+(Vector2& other)
{
	// TODO: insert return statement here
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	// TODO: insert return statement here
}

Vector2& Vector2::operator-(Vector2& other)
{
	// TODO: insert return statement here
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	// TODO: insert return statement here
}

Vector2& Vector2::operator*(const Vector2& other)
{
	// TODO: insert return statement here
}

float Vector2::Magnitude()
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

float toRadians(float angle)
{
	return angle * std::numbers::pi / 180;
}

Vector2 PolarCordinates(Vector2 referencePoint, float angle, float distance)
{
	float x = referencePoint.x + distance * cos(toRadians(angle));
	float y = referencePoint.y + distance * sin(toRadians(angle));
	return Vector2(x, y);
}