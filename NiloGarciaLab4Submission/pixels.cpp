#include "pixels.h"

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