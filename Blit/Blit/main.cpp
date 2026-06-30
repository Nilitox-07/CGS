#include "RasterSurface.h"

int main()
{
	unsigned int width = 500;
	unsigned int height = 500;

	RS_Initialize("niloGarcia", width, height);
	const unsigned int numPixels = width * height;
	unsigned int* rgbPixels = new unsigned int[numPixels];
	while (RS_Update(rgbPixels, numPixels))
	{

	}

	RS_Shutdown();

	return 0;
}