#pragma once
#include "Types.h"
#include <cmath>
#include <numbers>

struct Point
{
	float x;
	float y;

	Point();

	Point(float _x, float _y);

	float Magnitude();
};

float toRadians(float angle);

Point PolarCordinates(Point referencePoint, float angle, float distance);