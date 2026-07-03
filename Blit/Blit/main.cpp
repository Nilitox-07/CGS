#include "RasterSurface.h"
#include "Draw.h"
#include "Types.h"
#include "textures.h"

int main()
{
	ConvertImages();

	UINT width = 500;
	UINT height = 500;

	RS_Initialize("niloGarcia", width, height);
	Draw screen(width, height);

	Rect image(tiles_12_width, tiles_12_height);

	while (RS_Update(screen.GetSurface(), screen.GetPixels()))
	{
		screen.Fill(0xFF000FF000);
		screen.Blit(image, Point(), image.width, tiles_12_pixels, tiles_12_numpixels);
	}

	RS_Shutdown();

	return 0;
}