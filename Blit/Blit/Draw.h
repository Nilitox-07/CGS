#pragma once
#include "Types.h"
#include "Rect.h"
#include "pixels.h"
#include <cstring>

class Draw
{
public:

	void Fill(const UINT color);
	UINT _2Dto1D(UINT x, UINT y);
	void DrawPixel(const UINT color, Point pos);
	void Blit(Rect sourceRect, Point rasterPos, UINT sourceTextureWidth, const UINT* image, UINT imagePixels);
	void LineNx(const UINT color, Point point1, Point point2);

	Draw(UINT width, UINT height, bool _alphaBlending = true);

	UINT* GetSurface();
	UINT GetPixels();
	UINT GetWidth();
	UINT GetHeight();

private:


	Draw(const Draw&) = delete;
	Draw& operator=(const Draw&) = delete;

	UINT numPixels;
	UINT* surface;
	UINT width;
	UINT height;

	bool alphaBlending;
};

