#pragma once
#include "Draw.h"
#include <array>

class Shape
{
public:

	Shape(Point _position, UINT _sides, float _orientation);

	void DrawShape(Draw& screen, UINT startColor, UINT endColor);
	UINT GetSides();
	const std::vector<Point>& GetVertices();

protected:
	Point CalculateCentroid(std::vector<Point> _vertices);
	void CalculateVertices(float offset = 0.0f, float radius = 0.0f);
	void CalculateEdges();
	float CalculateOffset();
	void SetVertices(std::vector<Point> _vertices);

	Point position;
	UINT sides;
	float orientation;
	std::vector<Point> vertices;
	std::vector<std::array<Point, 2>> edges;
	
};

class Circle : public Shape
{
public:

	Circle(Point _position, float _radius);

private:

	float radius;
};

class Triangle: public Shape
{
public:

	Triangle(std::vector<Point> _vertices);
};

class Rectangles : public Shape
{
public:

	Rectangles(Point _position, float orientation, UINT width, UINT height);

private:

	float offset;

	UINT width;
	UINT height;
};

class CustomPolygon : public Shape
{
public:

	CustomPolygon(std::vector<Point> _vertices);
};

class AutoPolygon : public Shape
{
public:

	AutoPolygon(Point _position, UINT _sides, UINT _radius);

private:

	float offset;
	float radius;

};

