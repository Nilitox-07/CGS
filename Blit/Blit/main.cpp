#include "RasterSurface.h"
#include "Draw.h"
#include "Types.h"
#include "textures.h"
#include "Shape.h"
#include <vector>
#include <iostream>

void Display(Draw& screen);

Pixels red(0xFFFF0000, true);
Pixels green(0xFF00FF00, true);
Pixels blue(0xFF0000FF, true);
Pixels purple(0xFFFF00FF, true);
Pixels yellow(0xFFFFFF00, true);
Pixels cyan(0xFF00FFFF, true);
Pixels black(0xFF000000, true);
Pixels white(0xFFFFFFFF, true);

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

	RS_Initialize("Nilo Garcia: Lab 3", width, height);
	Draw screen(width, height);

	//AutoPolygon testPoly(Vector2(250, 250), 8, 150);
	Circle testPoly(Vector2(250, 250), 100);
	const std::vector<Vector2>& vertices = testPoly.GetVertices();


	std::vector<Pixels> colors = { red, green, blue, yellow, purple, cyan };

	while (RS_Update(screen.GetSurface(), screen.GetPixels()))
	{
		screen.Fill(black.ARGB);

		Display(screen);


		for (int i = 0; i < (int)vertices.size() / 2; i++)
		{
			//screen.ParametricLine(vertices[i], vertices[(i + ((int)testPoly.GetSides() / 2)) % (int)testPoly.GetSides()], colors[i % colors.size()].ARGB, colors[i % colors.size()].ARGB); 
			// This doesnt connect all vertices correctly on a odd number of vertices/sides
		}
		testPoly.DrawShape(screen, red.ARGB, blue.ARGB);

		clock.Signal();
	}

	RS_Shutdown();

	return 0;
}

void Display(Draw& screen)
{
}