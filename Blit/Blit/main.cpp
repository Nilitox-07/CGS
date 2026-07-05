#include "RasterSurface.h"
#include "Draw.h"
#include "Types.h"
#include "textures.h"
#include "Shape.h"
#include <vector>
#include <iostream>

void Display(Draw& screen);

int main()
{
#if 1
	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |
		_CRTDBG_CHECK_ALWAYS_DF |
		_CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(-1); // set block of memory to find memory leak
	_CrtDumpMemoryLeaks();

#endif

	srand(time(NULL));

	ConvertImages();

	UINT width = 500;
	UINT height = 500;

	XTime clock = XTime();

	RS_Initialize("Nilo Garcia: Lab 2", width, height);
	Draw screen(width, height);

	AutoPolygon testPoly(Point(250, 250), 8, 150);

	while (RS_Update(screen.GetSurface(), screen.GetPixels()))
	{
		screen.Fill(0xFF000000);

		//Display(screen);

		testPoly.DrawShape(screen, 0xFFFF0000, 0xFF0000FF);

		clock.Signal();
	}

	RS_Shutdown();

	return 0;
}

void Display(Draw& screen)
{
	screen.ParametricLine(Point(200, 200), Point(400, 400), 0xFFFF0000, 0xFF0000FF);
	screen.DrawPixel(0xFFFFFFFF, Point(200, 200));
	screen.DrawPixel(0xFFFFFFFF, Point(400, 400));
}