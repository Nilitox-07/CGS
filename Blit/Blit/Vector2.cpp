#include "Vector2.h"

Vector2::Vector2():
	x(0),
	y(0)
{
}

Vector2::Vector2(float _x, float _y) :
	x(_x),
	y(_y)
{
}

Vector2::Vector2(const Vector2& other):
	x(other.x),
	y(other.y)
{
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

Vector2 Vector2::operator+(Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;

	return *this;
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;

	return *this;
}

Vector2 Vector2::operator*(const Vector2& other) const
{
	return Vector2(x * other.x, y * other.y);
}

Vector2& Vector2::operator*=(const Vector2& other)
{
	x *= other.x;
	y *= other.y;

	return *this;
}

Vector2 Vector2::operator*(float value) const
{
	return Vector2(x * value, y * value);
}

Vector2& Vector2::operator*=(float value)
{
	x *= value;
	y *= value;
	
	return *this;
}

Vector2 Vector2::operator^(const Vector2& other) const
{
	return Vector2();
}

Vector2& Vector2::operator^=(const Vector2& other)
{
	return *this;
}

float Vector2::Magnitude() const
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

float Vector2::MagnitudeSquared() const
{
	return pow(x, 2) + pow(y, 2);
}

float Vector2::DistanceTo(const Vector2& other) const
{

	return ((*this) - other).Magnitude();
}

float Vector2::DistanceToSquared(const Vector2& other) const
{
	return ((*this) - other).MagnitudeSquared();
}

Vector2 Vector2::Normalize() const
{
	if (Magnitude() > 0)
		return Vector2(x / Magnitude(), y / Magnitude());
	return Vector2();
}

float Vector2::Dot(const Vector2& other) const
{
	return x * other.x + y * other.y;
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