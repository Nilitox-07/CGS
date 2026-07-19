#include "RasterSurface.h"
#include "Draw.h"
#include "Types.h"
#include "textures.h"
#include "Shape.h"
#include <vector>
#include <iostream>
#include "NxMath.h"
#include <numbers>
#include "Rendering.h"

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

	UINT width = 600;
	UINT height = 500;

	XTime clock = XTime();

	RS_Initialize("Nilo Garcia: Lab 4", width, height);
	Draw screen(width, height, Draw::NEEDS_DEPTH);

	std::vector<Pixels> colors = { red, green, blue, yellow, purple, cyan };

	// Material/Textures

	std::vector<Draw> materials;

	for (int currColor = 0; currColor < colors.size(); currColor++)
	{
		materials.push_back(Draw(256, 256));
		materials[currColor].Fill(colors[currColor].ARGB);
	}

	std::vector<Draw> textures = { dragon, tree, materials[0], materials[0], flower, celestial };

	// Grid

	UINT gridColor = green.ARGB;

	Vector3 Corners[4] =
	{
		Vector3(0.5f, 0, 0.5f),
		Vector3(0.5f, 0, -0.5f),
		Vector3(-0.5f, 0, -0.5f),
		Vector3(-0.5f, 0, 0.5f)
	};

	Vector3 borderVertices[18];
	int track = 0;
	for (float val = -0.4f; val < 0.5 && track < 18; val += 0.1f)
	{
		borderVertices[track] = Vector3(val, 0, 0.5f);
		track++;
		borderVertices[track] = Vector3(-0.5f, 0, val);
		track++;
	}

	Vector3 offsetVectors[2] =
	{
		Vector3(0, 0, -1),
		Vector3(1, 0, 0)
	};

	Matrix4 worldMatrix = Matrix4::Indentity();

	// Cube 1

	Vector3 cube1[8] =
	{
		Vector3(0.25f, 0.25f, 0.25f),
		Vector3(0.25f, 0.25f, -0.25f),
		Vector3(0.25f, -0.25f, 0.25f),
		Vector3(0.25f, -0.25f, -0.25f),
		Vector3(-0.25f, 0.25f, 0.25f),
		Vector3(-0.25f, 0.25f, -0.25f),
		Vector3(-0.25f, -0.25f, 0.25f),
		Vector3(-0.25f, -0.25f, -0.25f)
	};

	int cubeTriangles[36] =
	{
		0,1,2,
		0,2,3,

		4,5,6,
		4,6,7,

		8,9,10,
		8,10,11,

		12,13,14,
		12,14,15,

		16,17,18,
		16,18,19,

		20,21,22,
		20,22,23
	};

	float angle1 = 0.0f;

	UINT cube1Color = red.ARGB;

	Matrix4 cube1Matrix = Matrix4::Translation(Vector3(0, -0.25f, 0)) * Matrix4::RotationY(angle1);
	Vector3 worldCube1[8];
	Vector3 viewCube1[8];
	Vector3 projectedCube1[8];

	// Camara

	Matrix4 cameraMatrix = Matrix4::Indentity();

	cameraMatrix *= Matrix4::RotationX(-18 * std::numbers::pi_v<float> / 180.0f);
	cameraMatrix *= Matrix4::Translation(Vector3(0, 0, -1));

	Matrix4 viewMatrix = cameraMatrix.Inverse();

	// Projection

	float aspect = (float)screen.GetWidth() / screen.GetHeight();

	Matrix4 projectionMatrix = Matrix4::Perspective(90.0f * std::numbers::pi_v<float> / 180.0f, aspect, 0.1f, 10.0f);

	// Camara Transform

	Vector3 position = Vector3(0, 0, -1);
	Vector3 rotation = Vector3(-18, 0, 0);

	int current = 1;

	while (RS_Update(screen.GetSurface(), screen.GetPixels()))
	{
		if (GetAsyncKeyState('1') & 0x8000)
		{
			current = 1;
		}
		if (GetAsyncKeyState('2') & 0x8000)
		{
			current = 2;
			screen.TurnOffDepth();
		}
		if (GetAsyncKeyState('3') & 0x8000)
		{
			current = 3;
			screen.TurnOnDepth();
		}
		if (GetAsyncKeyState('4') & 0x8000)
		{
			current = 4;
			screen.TurnOnDepth();
		}

		screen.Fill(black.ARGB);

		screen.ClearDepthBuffer();

		Display(screen);

		// Updating Cube

		angle1 += clock.Delta() * 45;
		
		cube1Matrix = Matrix4::Translation(Vector3(0, -0.25f, 0)) * Matrix4::RotationY(angle1 * std::numbers::pi_v<float> / 180.0f);

		for (int i = 0; i < 8; i++)
		{
			// Shader

			worldCube1[i] = cube1Matrix.TransformPoint(cube1[i]);
			viewCube1[i] = viewMatrix.TransformPoint(worldCube1[i]);
			projectedCube1[i] = projectionMatrix.ProjectPoint(viewCube1[i]);

		}

		Vertex cubeVerticesFaces[24] =
		{
			// +X
			Vertex(projectedCube1[2], Vector2(0,0)),
			Vertex(projectedCube1[3], Vector2(1,0)),
			Vertex(projectedCube1[1], Vector2(1,1)),
			Vertex(projectedCube1[0], Vector2(0,1)),

			// -X
			Vertex(projectedCube1[4], Vector2(1,1)),
			Vertex(projectedCube1[5], Vector2(0,1)),
			Vertex(projectedCube1[7], Vector2(0,0)),
			Vertex(projectedCube1[6], Vector2(1,0)),

			// +Y
			Vertex(projectedCube1[0], Vector2(0,0)),
			Vertex(projectedCube1[1], Vector2(1,0)),
			Vertex(projectedCube1[5], Vector2(1,1)),
			Vertex(projectedCube1[4], Vector2(0,1)),

			// -Y
			Vertex(projectedCube1[6], Vector2(0,1)),
			Vertex(projectedCube1[7], Vector2(1,1)),
			Vertex(projectedCube1[3], Vector2(1,0)),
			Vertex(projectedCube1[2], Vector2(0,0)),

			// +Z
			Vertex(projectedCube1[0], Vector2(1,1)),
			Vertex(projectedCube1[2], Vector2(1,0)),
			Vertex(projectedCube1[6], Vector2(0,0)),
			Vertex(projectedCube1[4], Vector2(0,1)),

			// -Z
			Vertex(projectedCube1[1], Vector2(0,1)),
			Vertex(projectedCube1[5], Vector2(1,1)),
			Vertex(projectedCube1[7], Vector2(1,0)),
			Vertex(projectedCube1[3], Vector2(0,0))
		};

		// Grid

		for (int i = 0; i < 4; i++)
		{
			Vector3 start = projectionMatrix.ProjectPoint(viewMatrix.TransformPoint(Corners[i]));

			Vector3 end = projectionMatrix.ProjectPoint(viewMatrix.TransformPoint(Corners[(i + 1) % 4]));

			screen.LineNx(start.CartesianTo2D(screen), end.CartesianTo2D(screen), gridColor, gridColor, FLT_MAX / 2);
		}

		for (int i = 0; i < 18; i++)
		{
			Vector3 start = projectionMatrix.ProjectPoint(viewMatrix.TransformPoint(borderVertices[i]));

			Vector3 end = projectionMatrix.ProjectPoint(viewMatrix.TransformPoint(borderVertices[i] + offsetVectors[i % 2]));

			screen.LineNx(start.CartesianTo2D(screen), end.CartesianTo2D(screen), gridColor, gridColor, FLT_MAX / 2);
		}

		// Cube

		if (current == 1)
		{
			for (int i = 0; i < 8; i++)
			{
				for (int bit = 0; bit < 3; bit++)
				{
					int other = i ^ (1 << bit);

					if (i < other)
					{
						screen.LineNx(projectedCube1[i].CartesianTo2D(screen), projectedCube1[other].CartesianTo2D(screen), cube1Color, cube1Color, FLT_MAX / 2);
					}
				}
			}
		}

		if (current == 2 || current == 3)
		{
			for (int i = 0; i < 36; i += 3)
			{
				Vertex a = cubeVerticesFaces[cubeTriangles[i]];
				Vertex b = cubeVerticesFaces[cubeTriangles[i + 1]];
				Vertex c = cubeVerticesFaces[cubeTriangles[i + 2]];

				DrawTriangle(a, b, c, materials[i / 6], screen);
			}
		}

		if (current == 4)
		{
			for (int i = 0; i < 36; i += 3)
			{
				Vertex a = cubeVerticesFaces[cubeTriangles[i]];
				Vertex b = cubeVerticesFaces[cubeTriangles[i + 1]];
				Vertex c = cubeVerticesFaces[cubeTriangles[i + 2]];

				DrawTriangle(a, b, c, textures[i / 6], screen);
			}
		}

		clock.Signal();
	}

	RS_Shutdown();

	return 0;
}

void Display(Draw& screen)
{
}