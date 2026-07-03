#include "RasterSurface.h"
#include "Draw.h"
#include "Types.h"
#include "textures.h"

void Display(Draw& screen);

int main()
{
	ConvertImages();

	UINT width = 500;
	UINT height = 500;

	RS_Initialize("niloGarcia", width, height);
	Draw screen(width, height);

	while (RS_Update(screen.GetSurface(), screen.GetPixels()))
	{
		Display(screen);
	}

	RS_Shutdown();

	return 0;
}

void Display(Draw& screen)
{
	Rect imageRect(32, 32, Point(288, 128));
	Draw imageSprite(imageRect, true);
	imageSprite.SetImage(tiles_12_pixels, tiles_12_width, tiles_12_height);

	Rect grassTileRect(32, 32);
	Draw grassTileSprite(grassTileRect, false);
	grassTileSprite.Blit(imageRect, Point(), imageSprite);

	for (int y = 0; y <= screen.GetHeight() / grassTileRect.height; y++)
	{
		for (int x = 0; x <= screen.GetWidth() / grassTileRect.width; x++)
		{
			screen.Blit(grassTileRect, Point(x * grassTileSprite.GetWidth(), y * grassTileSprite.GetHeight()), grassTileSprite);
		}
	}

	
}