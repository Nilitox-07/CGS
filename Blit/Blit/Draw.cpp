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

void Draw::DrawPixel(UINT* colorBuffer, const UINT color, const UINT x, const UINT y, const UINT width)
{
	colorBuffer[Draw::GetInstance()._2Dto1D(x, y, width)] = color;
}

void Draw::Blit(UINT* colorBuffer, Rect sourceRect, Point rasterPos, UINT sourceTextureWidth, UINT* image)
{
	//for (UINT* bufferPtr = colorBuffer + rasterPos.x; bufferPtr)
}
