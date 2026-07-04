#include "RasterSurface.h"
#include "Draw.h"
#include "Types.h"
#include "textures.h"
#include <vector>
#include <iostream>

void Display(Draw& screen);

int main()
{
#if 1
	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |
		_CRTDBG_CHECK_ALWAYS_DF |
		_CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(CodeBlock); // set block of memory to find memory leak
	_CrtDumpMemoryLeaks();

#endif

	srand(time(NULL));

	ConvertImages();

	UINT width = 500;
	UINT height = 500;

	XTime clock = XTime();

	std::vector<Point> randomObjectsPosition;
	std::vector<int> randomObjects;
	for (int i = 0; i < 20; i++)
	{
		Point randPos(rand() % width, rand() % height);
		randomObjectsPosition.push_back(randPos);
		randomObjects.push_back(rand() % 4);
	}
	randomObjectsPosition.push_back(Point(498, 0));
	randomObjects.push_back(0);

	RS_Initialize("Nilo Garcia: Lab 1", width, height);
	Draw screen(width, height);

	Rect imageRect(32, 32, Point(288, 128));
	Draw imageSprite(imageRect, true);
	imageSprite.SetImage(tiles_12_pixels, tiles_12_width, tiles_12_height);

	Draw fireAnimation(fire_02_width, fire_02_height, true, true, 30, &screen);
	fireAnimation.SetImage(fire_02_pixels, fire_02_width, fire_02_height);

	Draw objectToDrawSprite(16 * 4, 16, false);
	objectToDrawSprite.Blit(Rect(16 * 4, 16, Point(16, 192)), Point(0, 0), imageSprite);

	Draw objectToPrint(16, 16, true);
	//objectToPrint.Fill(0x00000000);

	while (RS_Update(screen.GetSurface(), screen.GetPixels()))
	{
		Display(screen);

		for (int i = 0; i < randomObjectsPosition.size(); i++)
		{
			objectToPrint.Blit(Rect(16, 16, Point(randomObjects[i] * 16, 0)), Point(), objectToDrawSprite);
			screen.Blit(Rect(16, 16), randomObjectsPosition[i], objectToPrint);
		}

		screen.LoadAnimation(fireAnimation, Point(250, 250), fireAnimation.GetWidth() / 8, fireAnimation.GetHeight() / 8, clock); // This function only works with animations that will remain throught the whole program.
		
		// There is a way to optimize how the animation is being display. Since the animation only gets updated every 1/30th of a second, i could be updating the display only when the animation changes.
		// But even for that i would need to either take in Display function or something in that style. The other way i am thinking is having 2 different display functions. Display() and UpdateDisplay(). 
		// That second function would be using dirty sprites to update the screen and the dirty sprites would be coming from any function that updates the screen.

		clock.Signal();
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