#pragma once
#include "Draw.h"
#include <array>

class Shape
{
public:

	Shape(Vector2 _position, UINT _sides, float _orientation);

	void DrawShape(Draw& screen, UINT startColor, UINT endColor);
	UINT GetSides();
	const std::vector<Vector2>& GetVertices();

protected:
	Vector2 CalculateCentroid(std::vector<Vector2> _vertices);
	void CalculateVertices(float offset = 0.0f, float radius = 0.0f);
	void CalculateEdges();
	float CalculateOffset();
	void SetVertices(std::vector<Vector2> _vertices);

	Vector2 position;
	UINT sides;
	float orientation;
	std::vector<Vector2> vertices;
	std::vector<std::array<Vector2, 2>> edges;
	
};

class Circle : public Shape
{
public:

	Circle(Vector2 _position, float _radius);

private:

	float radius;
};

class Triangle: public Shape
{
public:

	Triangle(std::vector<Vector2> _vertices);
};

class Rectangles : public Shape
{
public:

	Rectangles(Vector2 _position, float orientation, UINT width, UINT height);

private:

	float offset;

	UINT width;
	UINT height;
};

class CustomPolygon : public Shape
{
public:

	CustomPolygon(std::vector<Vector2> _vertices);
};

class AutoPolygon : public Shape
{
public:

	AutoPolygon(Vector2 _position, UINT _sides, UINT _radius);

private:

	float offset;
	float radius;

};

