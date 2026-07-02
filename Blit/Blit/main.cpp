#include "RasterSurface.h"
#include "Draw.h"
#include "Types.h"

int main()
{
	UINT width = 500;
	UINT height = 500;

	RS_Initialize("niloGarcia", width, height);
	const UINT numPixels = width * height;
	UINT* rgbPixels = new UINT[numPixels];
	while (RS_Update(rgbPixels, numPixels))
	{
		Draw::GetInstance().Fill(rgbPixels, 0xFF557711, numPixels);
		Draw::GetInstance().DrawPixel(rgbPixels, 0xFFFFFFFF, Point(200, 500), width);
		Draw::GetInstance().Line(rgbPixels, 0xFFFFFFFF, Point(170, 60), Point(320, 60), width);
	}

	RS_Shutdown();

	return 0;
}