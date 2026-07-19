#include "Vector3.h"
#include "NxMath.h"
#include "Draw.h"

Vector3::Vector3():
	x(0),
	y(0),
	z(0)
{

}

Vector3::Vector3(float _x, float _y, float _z) :
	x(_x),
	y(_y),
	z(_z)
{}

Vector3::Vector3(const Vector3& other):
	x(other.x),
	y(other.y),
	z(other.z)
{

}

Vector3& Vector3::operator=(const Vector3 & other)
{
	if (this != &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}
	return *this;
}

Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

Vector3 Vector3::operator-(const Vector3& other) const
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}
Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

Vector3 Vector3::operator*(const Vector3& other) const
{
	return Vector3(x * other.x, y * other.y, z * other.z);
}

Vector3 Vector3::operator*(const float value) const
{
	return Vector3(x * value, y * value, z * value);
}

Vector3& Vector3::operator*=(const Vector3& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;

	return *this;
}

Vector3 Vector3::operator^(const Vector3& other) const
{
	Vector3 toReturn;

	toReturn.x = y * other.z - z * other.y;
	toReturn.y = z * other.x - x * other.z;
	toReturn.z = x * other.y - y * other.x;

	return toReturn;
}

Vector3& Vector3::operator^=(const Vector3& other)
{
	float oldX = x;
	float oldY = y;
	float oldZ = z;

	x = oldY * other.z - oldZ * other.y;
	y = oldZ * other.x - oldX * other.z;
	z = oldX * other.y - oldY * other.x;

	return *this;
}	    

float Vector3::Magnitude() const
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

float Vector3::MagnitudeSquared() const
{
	return pow(x, 2) + pow(y, 2) + pow(z, 2);
}

float Vector3::DistanceTo(const Vector3& other) const
{
	return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2));
}

float Vector3::DistanceSquaredTo(const Vector3& other) const
{
	return pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2);
}

Vector3 Vector3::Normalize() const
{
	float mag = Magnitude();
	if (mag > 0)
		return Vector3(x / mag, y / mag, z / mag);
	return Vector3();
}

float Vector3::Dot(const Vector3& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

Vector2 Vector3::CartesianTo2D(const Draw& screen)
{
	Vector2 screenCenter = Vector2(screen.GetWidth() / 2, screen.GetHeight() / 2);

	Vector2 toReturn;
	Vector2 TwoDPosition = Vector2(x, -y);

	TwoDPosition *= screenCenter;
	TwoDPosition += Vector2(0.5, 0.5);

	toReturn += TwoDPosition;
	toReturn += screenCenter;

	return toReturn;
}

Barycentric FindBarycentric(Vector2 a, Vector2 b, Vector2 c, Vector2 point)
{
	float denominator = ((b.y - c.y) * (a.x - c.x) + (c.x - b.x) * (a.y - c.y));

	float alpha = ((b.y - c.y) * (point.x - c.x) + (c.x - b.x) * (point.y - c.y)) / denominator;

	float beta = ((c.y - a.y) * (point.x - c.x) + (a.x - c.x) * (point.y - c.y)) / denominator;

	float gamma = 1.0f - alpha - beta;

	return Barycentric(alpha, beta, gamma);
}