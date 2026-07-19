#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4.h"
#include <cmath>

struct Rect
{
	UINT width;
	UINT height;
	Vector2 pos;

	Rect(UINT _width, UINT _height, Vector2 _pos = Vector2())
	{
		width = _width;
		height = _height;
		pos = _pos;
	}
};

struct Barycentric
{
	float alpha;
	float beta;
	float gamma;

	Barycentric(float _alpha, float _beta, float _gamma) :
		alpha(_alpha),
		beta(_beta),
		gamma(_gamma)
	{

	}
};

struct Vertex
{
	Vector3 position;
	Vector2 uv;

	Vertex() :
		position(Vector3()),
		uv(Vector2())
	{

	}

	Vertex(Vector3 _position, Vector2 _uv):
		position(_position),
		uv(_uv)
	{

	}
};

