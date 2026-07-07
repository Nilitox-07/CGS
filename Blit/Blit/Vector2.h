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
	Vector2& operator+(Vector2& other);
	Vector2& operator+=(const Vector2& other);
	Vector2& operator-(Vector2& other);
	Vector2& operator-=(const Vector2& other);
	Vector2& operator*(const Vector2& other);

	float Magnitude();
};

float toRadians(float angle);

Vector2 PolarCordinates(Vector2 referencePoint, float angle, float distance);