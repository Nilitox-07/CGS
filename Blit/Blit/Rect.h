#pragma once
#include "Types.h"
#include "Vector2.h"
#include <math.h>

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