#pragma once
#include "Types.h"
#include "Point.h"

struct Rect
{
	UINT width;
	UINT height;
	Point pos;

	Rect(UINT _width, UINT _height, Point _pos)
	{
		width = _width;
		height = _height;
		pos = _pos;
	}
};