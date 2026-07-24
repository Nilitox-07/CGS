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

	Pixels();
	Pixels(UINT BGRA);
	Pixels(UINT ARGB, bool dif);
	Pixels& operator=(const Pixels& other);

	Pixels& operator+=(const Pixels& other);
	Pixels operator+(const Pixels& other);
	Pixels& operator-=(const Pixels& other);
	Pixels operator-(const Pixels& other);
	Pixels& operator*=(const Pixels& other);
	Pixels operator*(const Pixels& other);


	void Lerp(Pixels other, float percentage = 1.0f);

	void ARGB_Func();
};