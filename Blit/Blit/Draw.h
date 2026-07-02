#pragma once
#include "Types.h"
#include "Rect.h"

class Draw
{
public:

	static Draw& GetInstance();

	void Fill(UINT* colorBuffer, const UINT color, const UINT numPixels);
	UINT _2Dto1D(UINT x, UINT y, UINT width);
	void DrawPixel(UINT* colorBuffer, const UINT color, Point pos, const UINT width);
	void Blit(UINT* colorBuffer, Rect sourceRect, Point rasterPos, UINT sourceTextureWidth, UINT* image);
	void Line(UINT* colorBuffer, const UINT color, Point point1, Point point2, UINT width);

private:

	Draw();

	Draw(const Draw&) = delete;
	Draw& operator=(const Draw&) = delete;

};

