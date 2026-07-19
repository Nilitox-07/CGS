#pragma once
#include "Types.h"
#include <cmath>
#include <numbers>

struct Vector2;
struct Barycentric;
class Draw;

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3();
	Vector3(float _x, float _y, float _z);
	Vector3(const Vector3& other);
	Vector3& operator=(const Vector3& other);
	Vector3 operator+(const Vector3& other) const;
	Vector3& operator+=(const Vector3& other);
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator-() const;
	Vector3& operator-=(const Vector3& other);
	Vector3 operator*(const Vector3& other) const;
	Vector3 operator*(const float value) const;
	Vector3& operator*=(const Vector3& other);
	Vector3 operator^(const Vector3& other) const;
	Vector3& operator^=(const Vector3& other);

	float Magnitude() const;
	float MagnitudeSquared() const;
	float DistanceTo(const Vector3& other) const;
	float DistanceSquaredTo(const Vector3& other) const;
	Vector3 Normalize() const;
	float Dot(const Vector3& other) const;

	Vector2 CartesianTo2D(const Draw& screen);


};

Barycentric FindBarycentric(Vector2 a, Vector2 b, Vector2 c, Vector2 point);