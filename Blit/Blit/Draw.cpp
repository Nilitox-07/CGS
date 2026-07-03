#include "Draw.h"

Draw::Draw(UINT _width, UINT _height, bool _alphaBlending) : 
	width(_width), 
	height(_height), 
	numPixels(_width * _height),
	surface(new UINT[numPixels]),
	alphaBlending(_alphaBlending)
{

}

UINT* Draw::GetSurface()
{
	return surface;
}

UINT Draw::GetPixels()
{
	return numPixels;
}

UINT Draw::GetWidth()
{
	return width;
}

UINT Draw::GetHeight()
{
	return height;
}


void Draw::Fill(const UINT color)
{
	for (unsigned int* currentPtr = surface; currentPtr != surface + numPixels; currentPtr++)
	{
		*currentPtr = color;
	}
}

UINT Draw::_2Dto1D(UINT x, UINT y)
{
	return x + y * width;
}

void Draw::DrawPixel(const UINT color, Point pos)
{
	surface[_2Dto1D((int)pos.x, (int)pos.y)] = color;
}

void Draw::Blit(Rect sourceRect, Point rasterPos, UINT sourceTextureWidth, const UINT* image, UINT imagePixels)
{
	if (alphaBlending)
	{
		for (int y = 0; y < sourceRect.height; y++)
		{
			for (int x = 0; x < sourceRect.width; x++)
			{
				Pixels destination(*(surface + (int)rasterPos.x + x + (width * y)), true);
				Pixels source(*(image + x + (sourceRect.width * y)), true);
				destination.Lerp(source);
				*(surface + (int)rasterPos.x + x + (width * y)) = destination.ARGB;
			}
		}
	}
	else
	{
		const UINT* imagePtr = image + (int)sourceRect.pos.x;

		for (UINT* bufferPtr = surface + (int)rasterPos.x; bufferPtr < surface + numPixels && imagePtr < image + imagePixels; bufferPtr += width)
		{
			std::memcpy(bufferPtr, imagePtr, sourceRect.width * sizeof(UINT));
			imagePtr += sourceTextureWidth;
		}
	}
}

void Draw::LineNx(const UINT color, Point point1, Point point2)
{
	if (point1.x == point2.x)
	{
		for (int y = fmin(point1.y, point2.y); y < fmin(point1.y, point2.y) + fabs(point1.y - point2.y); y++)
		{
			DrawPixel(color, Point(point1.x, y));
		}
		return;
	}
	float slope = (point2.y - point1.y) / (point2.x - point1.x);
	float intercept = point1.y - slope * point1.x;
	if (fabs(point1.x - point2.x) >= fabs(point1.y - point2.y))
	{
		for (int x = fmin(point1.x, point2.x); x < fmin(point1.x, point2.x) + fabs(point1.x - point2.x); x++)
		{
			DrawPixel(color, Point(x, slope * x + intercept));
		}
	}
	else
	{
		for (int y = fmin(point1.y, point2.y); y < fmin(point1.y, point2.y) + fabs(point1.y - point2.y); y++)
		{
			DrawPixel(color, Point((y - intercept)/slope, y));
		}
	}
}