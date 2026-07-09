#pragma once
#include "Types.h"
#include <cmath>
#include <numbers>

struct Vector3
{

	Vector3();
	Vector3(float x, float y, float z);
	Vector3& operator=(const Vector3& other);
	Vector3(const Vector3& other);
	Vector3 operator+(const Vector3& other);
	Vector3& operator+=(const Vector3& other);
	Vector3 operator-(const Vector3& other);
	Vector3& operator-=(const Vector3& other);
	Vector3 operator*(const Vector3& other);
	Vector3& operator*=(const Vector3& other);
	Vector3 operator^(const Vector3& other);
	Vector3& operator^=(const Vector3& other);

	float Magnitude();
	float MagnitudeSquared();
	float DistanceTo(const Vector3& other);
	float DistanceSquaredTo(const Vector3& other);
	Vector3 Normalize();
	float Dot(const Vector3& other);

	float x;
	float y;
	float z;

};

