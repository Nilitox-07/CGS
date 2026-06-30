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
	}

	RS_Shutdown();

	return 0;
}