#include "Shape.h"

Shape::Shape(Vector2 _position, UINT _sides, float _orientation) :
	position(_position),
	sides(_sides),
	orientation(_orientation)
{
}

Vector2 Shape::CalculateCentroid(std::vector<Vector2> _vertices)
{
	float x = 0;
	float y = 0;

	for (int i = 0; i < (int)_vertices.size(); i++)
	{
		x += _vertices[i].x;
		y += _vertices[i].y;
	}
	x /= (int)_vertices.size();
	y /= (int)_vertices.size();

	return Vector2(x, y);
}

void Shape::CalculateVertices(float offset, float radius)
{
	float degree = orientation + offset;
	float degreeInterval = 360.0f / sides;
	for (int i = 0; i < sides; i++)
	{
		vertices.push_back(PolarCordinates(position, degreeInterval * i + degree, radius));
	}
}

void Shape::CalculateEdges()
{
	for (int i = 0; i < sides; i++)
	{
		edges.push_back({ vertices[i], vertices[(i + 1) % sides] });
	}
}

float Shape::CalculateOffset()
{
	return 90 - 180.0f / sides;
}

void Shape::SetVertices(std::vector<Vector2> _vertices)
{
	vertices = _vertices;
}

void Shape::DrawShape(Draw& screen, UINT startColor, UINT endColor)
{
	for (int i = 0; i < edges.size(); i++)
	{
		Pixels firstColorPx(startColor, true);
		Pixels secondColorPx(startColor, true);
		Pixels endColorPx(endColor, true);

		firstColorPx.Lerp(endColorPx, i * 1.0f / edges.size());
		secondColorPx.Lerp(endColorPx, ((i + 1) * 1.0f) / edges.size());

		screen.ParametricLine(edges[i][0], edges[i][1], firstColorPx.ARGB, secondColorPx.ARGB);
		//screen.LineNx(edges[i][0], edges[i][1], firstColorPx.ARGB, secondColorPx.ARGB);
	}
}

UINT Shape::GetSides()
{
	return sides;
}

const std::vector<Vector2>& Shape::GetVertices()
{
	return vertices;
}

Circle::Circle(Vector2 _position, float _radius) :
	Shape(_position, 50, 0),
	radius(_radius)
{
	CalculateVertices(0, radius);
	CalculateEdges();
}

Triangle::Triangle(std::vector<Vector2> _vertices) :
	Shape(CalculateCentroid(_vertices), 3, 0)
{
	vertices = _vertices;
	CalculateEdges();
}

Rectangles::Rectangles(Vector2 _position, float orientation, UINT _width, UINT _height) :
	Shape(_position, 4, 0),
	offset(CalculateOffset()),
	width(_width),
	height(_height)
{
	CalculateVertices(offset, Vector2(width / 2.0f, height / 2.0f).Magnitude());
	CalculateEdges();
}

CustomPolygon::CustomPolygon(std::vector<Vector2> _vertices):
	Shape(CalculateCentroid(_vertices), _vertices.size(), 0)
{
	SetVertices(_vertices);
	CalculateEdges();
}

AutoPolygon::AutoPolygon(Vector2 _position, UINT _sides, UINT _radius) :
	Shape(_position, _sides, 0),
	offset(CalculateOffset()),
	radius(_radius)
{
	CalculateVertices(offset, radius);
	CalculateEdges();
}
