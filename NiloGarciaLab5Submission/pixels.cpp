#include "pixels.h"

Pixels::Pixels() :
	alpha(0),
	red(0),
	green(0),
	blue(0),
	ARGB(0)
{

}

Pixels::Pixels(UINT BGRA) :
	alpha(BGRA & 0xFF),
	red((BGRA >> 8) & 0xFF),
	green((BGRA >> 16) & 0xFF),
	blue((BGRA >> 24) & 0xFF),
	ARGB(BGRA)
{
	ARGB_Func();
}

Pixels::Pixels(UINT ARGB, bool dif) :
	blue(ARGB & 0xFF),
	green((ARGB >> 8) & 0xFF),
	red((ARGB >> 16) & 0xFF),
	alpha((ARGB >> 24) & 0xFF),
	ARGB(ARGB)
{

}
Pixels& Pixels::operator=(const Pixels& other)
{
	red = other.red;
	blue = other.blue;
	green = other.green;
	alpha = other.alpha;
	ARGB = other.ARGB;

	return *this;
}
Pixels& Pixels::operator+=(const Pixels& other)
{
	red = min(red + other.red, 255);
	blue = min(blue + other.blue, 255);
	green = min(green + other.green, 255);
	alpha = min(alpha + other.alpha, 255);
	ARGB_Func();

	return *this;
}
Pixels Pixels::operator+(const Pixels& other)
{
	Pixels temp;

	temp.red = min(red + other.red, 255);
	temp.blue = min(blue + other.blue, 255);
	temp.green = min(green + other.green, 255);;
	temp.alpha = min(alpha + other.alpha, 255);;
	temp.ARGB_Func();

	return temp;
}
Pixels& Pixels::operator-=(const Pixels& other)
{
	red = max(red - other.red, 0);
	blue = max(blue - other.blue, 0);
	green = max(green - other.green, 0);
	alpha = max(alpha - other.alpha, 0);
	ARGB_Func();

	return *this;
}
Pixels Pixels::operator-(const Pixels& other)
{
	Pixels temp;

	temp.red = max(red - other.red, 0);
	temp.blue = max(blue - other.blue, 0);
	temp.green = max(green - other.green, 0);
	temp.alpha = max(alpha - other.alpha, 0);
	ARGB_Func();

	return temp;
}
Pixels& Pixels::operator*=(const Pixels& other)
{
	red = (red / 255.0f) * (other.red / 255.0f) * 255.0f;
	blue = (blue / 255.0f) * (other.blue / 255.0f) * 255.0f;
	green = (green / 255.0f) * (other.green / 255.0f) * 255.0f;
	alpha = (alpha / 255.0f) * (other.alpha / 255.0f) * 255.0f;
	ARGB_Func();

	return *this;
}
Pixels Pixels::operator*(const Pixels& other)
{
	Pixels temp;

	temp.red = red * (other.red / 255);
	temp.blue = blue * (other.blue / 255);
	temp.green = green * (other.green / 255);
	temp.alpha = alpha * (other.alpha / 255);
	ARGB_Func();

	return temp;
}
void Pixels::Lerp(Pixels other, float percentage)
{
	float reciprocal = 1.0f / 255.0f;
	float ratio = other.alpha * reciprocal * percentage;
	red = std::lerp(red, other.red, ratio);
	green = std::lerp(green, other.green, ratio);
	blue = std::lerp(blue, other.blue, ratio);
	alpha = std::lerp(alpha, other.alpha, ratio);
	ARGB_Func();
}

void Pixels::ARGB_Func()
{
	ARGB = (alpha << 24) | (red << 16) | (green << 8) | (blue);
}