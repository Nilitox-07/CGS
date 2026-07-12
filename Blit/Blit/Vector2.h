#pragma once
#include "Types.h"
#include <cmath>
#include <numbers>

struct Vector2
{
	float x;
	float y;

	Vector2();
	Vector2(float _x, float _y);
	Vector2(const Vector2& other);
	Vector2& operator=(const Vector2& other);
	Vector2 operator+(Vector2& other) const;
	Vector2& operator+=(const Vector2& other);
	Vector2 operator-(const Vector2& other) const;
	Vector2& operator-=(const Vector2& other);
	Vector2 operator*(const Vector2& other) const;
	Vector2& operator*=(const Vector2& other);
	Vector2 operator*(float value) const;
	Vector2& operator*=(float value);
	Vector2 operator^(const Vector2& other) const;
	Vector2& operator^=(const Vector2& other);

	float Magnitude() const;
	float MagnitudeSquared() const;
	float DistanceTo(const Vector2& other) const;
	float DistanceToSquared(const Vector2& other) const;
	Vector2 Normalize() const;
	float Dot(const Vector2& other) const;
	//float AngleBetween(const Vector2& other) const;
};

float toRadians(float angle);

Vector2 PolarCordinates(Vector2 referencePoint, float angle, float distance);