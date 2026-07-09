#include "Vector3.h"

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

Vector3::Vector3(const Vector3& other):
	x(other.x),
	y(other.y),
	z(other.z)
{

}

Vector3 Vector3::operator+(const Vector3& other)
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

Vector3 Vector3::operator-(const Vector3& other)
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

Vector3 Vector3::operator*(const Vector3& other)
{
	return Vector3(x * other.x, y * other.y, z * other.z);
}

Vector3& Vector3::operator*=(const Vector3& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;

	return *this;
}

Vector3 Vector3::operator^(const Vector3& other)
{
	return Vector3(y * other.z - z * other.y, 
				   z * other.x - x * other.z,
				   x * other.y - y * other.x);
}

Vector3& Vector3::operator^=(const Vector3& other)
{
	x = y * other.z - z * other.y;
	y = z * other.x - x * other.z;
	z = x * other.y - y * other.x;

	return *this;
}	    

float Vector3::Magnitude()
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

float Vector3::MagnitudeSquared()
{
	return pow(x, 2) + pow(y, 2) + pow(z, 2);
}

float Vector3::DistanceTo(const Vector3& other)
{
	return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2));
}

float Vector3::DistanceSquaredTo(const Vector3& other)
{
	return pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2);
}

Vector3 Vector3::Normalize()
{
	float mag = Magnitude();
	if (mag > 0)
		return Vector3(x / mag, y / mag, z / mag);
	return Vector3();
}

float Vector3::Dot(const Vector3& other)
{
	return x * other.x + y * other.y + z * other.z;
}
