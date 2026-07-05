#include "Point.h"

Point::Point()
{
	x = 0;
	y = 0;
}

Point::Point(float _x, float _y)
{
	x = _x;
	y = _y;
}

float Point::Magnitude()
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

float toRadians(float angle)
{
	return angle * std::numbers::pi / 180;
}

Point PolarCordinates(Point referencePoint, float angle, float distance)
{
	float x = referencePoint.x + distance * cos(toRadians(angle));
	float y = referencePoint.y + distance * sin(toRadians(angle));
	return Point(x, y);
}