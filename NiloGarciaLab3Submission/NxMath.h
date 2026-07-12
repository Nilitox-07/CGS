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