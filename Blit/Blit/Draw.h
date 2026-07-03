#pragma once
#include "Types.h"
#include "Rect.h"
#include "pixels.h"
#include <cstring>

class Draw
{
public:
	
	Draw(UINT width, UINT height, bool _alphaBlending = true);
	Draw(Rect imageRect, bool _alphaBlending = true);

	void Fill(const UINT color);
	UINT _2Dto1D(UINT x, UINT y);
	void DrawPixel(const UINT color, Point pos);
	void Blit(Rect sourceRect, Point rasterPos, Draw& image);
	void LoadAnimation(Draw& spriteSheet, Point rasterPos, UINT imageSizeWidth, UINT imageSizeHeight);
	void LineNx(const UINT color, Point point1, Point point2);

	UINT* GetSurface();
	UINT GetPixels();
	UINT GetWidth();
	UINT GetHeight();
	UINT* GetPixel(Point pos);
	void SetImage(UINT* image, UINT _width, UINT _height);
	void Resize(UINT _width, UINT _height);

private:


	Draw(const Draw&) = delete;
	Draw& operator=(const Draw&) = delete;

	UINT numPixels;
	UINT* surface;
	UINT width;
	UINT height;

	bool alphaBlending;
};

