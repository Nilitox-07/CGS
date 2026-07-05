#pragma once
#include "Types.h"
#include <cmath>

struct Pixels
{
	UINT alpha;
	UINT red;
	UINT green;
	UINT blue;
	UINT ARGB;

	Pixels(UINT BGRA) : 
		alpha(BGRA & 0xFF),
		red((BGRA >> 8) & 0xFF),
		green((BGRA >> 16) & 0xFF),
		blue((BGRA >> 24) & 0xFF),
		ARGB(BGRA)
	{
		ARGB_Func();
	}
	Pixels(UINT ARGB, bool dif) :
		blue(ARGB & 0xFF),
		green((ARGB >> 8) & 0xFF),
		red((ARGB >> 16) & 0xFF),
		alpha((ARGB >> 24) & 0xFF),
		ARGB(ARGB)	
	{

	}

	void Lerp(Pixels other, float percentage = 1.0f)
	{
		float reciprocal = 1.0f / 255.0f;
		float ratio = other.alpha * reciprocal * percentage;
		red = std::lerp(red, other.red, ratio);
		green = std::lerp(green, other.green, ratio);
		blue = std::lerp(blue, other.blue, ratio);
		alpha = std::lerp(alpha, other.alpha, ratio);
		ARGB_Func();
	}

	void ARGB_Func()
	{
		ARGB = (alpha << 24) | (red << 16) | (green << 8) | (blue);
	}
};