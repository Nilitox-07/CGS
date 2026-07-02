#include "Draw.h"

Draw::Draw()
{

}

Draw& Draw::GetInstance()
{
	static Draw instance;
	return instance;
}


void Draw::Fill(UINT* colorBuffer, const UINT color, const UINT numPixels)
{
	for (unsigned int* currentPtr = colorBuffer; currentPtr != colorBuffer + numPixels; currentPtr++)
	{
		*currentPtr = color;
	}
}

UINT Draw::_2Dto1D(UINT x, UINT y, UINT width)
{
	return x + y * width;
}

void Draw::DrawPixel(UINT* colorBuffer, const UINT color, Point pos, const UINT width)
{
	colorBuffer[Draw::GetInstance()._2Dto1D((int)pos.x, (int)pos.y, width)] = color;
}

void Draw::Blit(UINT* colorBuffer, Rect sourceRect, Point rasterPos, UINT sourceTextureWidth, UINT* image)
{
	//for (UINT* bufferPtr = colorBuffer + rasterPos.x; bufferPtr)
}

void Draw::Line(UINT* colorBuffer, const UINT color, Point point1, Point point2, UINT width)
{
	if (point1.x == point2.x)
	{
		for (int y = fmin(point1.y, point2.y); y < fmin(point1.y, point2.y) + fabs(point1.y - point2.y); y++)
		{
			Draw::GetInstance().DrawPixel(colorBuffer, color, Point(point1.x, y), width);
		}
		return;
	}
	float slope = (point2.y - point1.y) / (point2.x - point1.x);
	float intercept = point1.y - slope * point1.x;
	if (fabs(point1.x - point2.x) >= fabs(point1.y - point2.y))
	{
		for (int x = fmin(point1.x, point2.x); x < fmin(point1.x, point2.x) + fabs(point1.x - point2.x); x++)
		{
			Draw::GetInstance().DrawPixel(colorBuffer, color, Point(x, slope * x + intercept), width);
		}
	}
	else
	{
		for (int y = fmin(point1.y, point2.y); y < fmin(point1.y, point2.y) + fabs(point1.y - point2.y); y++)
		{
			Draw::GetInstance().DrawPixel(colorBuffer, color, Point((y - intercept)/slope, y), width);
		}
	}
}