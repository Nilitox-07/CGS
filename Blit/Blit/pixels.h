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

	Pixels(UINT BGRA);
	Pixels(UINT ARGB, bool dif);

	void Lerp(Pixels other, float percentage = 1.0f);

	void ARGB_Func();
};