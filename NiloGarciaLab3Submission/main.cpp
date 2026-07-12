#include "RasterSurface.h"
#include "Draw.h"
#include "Types.h"
#include "textures.h"
#include "Shape.h"
#include <vector>
#include <iostream>
#include "NxMath.h"
#include <numbers>

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

	std::vector<Pixels> colors = { red, green, blue, yellow, purple, cyan };

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

	float angle1 = 0.0f;

	UINT cube1Color = yellow.ARGB;

	Matrix4 cube1Matrix = Matrix4::Translation(Vector3(0, -0.25f, 0)) * Matrix4::RotationY(angle1);
	Vector3 worldCube1[8];
	Vector3 viewCube1[8];
	Vector3 projectedCube1[8];

	// Cube 2

	Vector3 cube2[8] =
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

	float angle2 = 0.0f;

	UINT cube2Color = purple.ARGB;

	Matrix4 cube2Matrix = Matrix4::Translation(Vector3(0, -0.25f, 0)) * Matrix4::RotationY(angle2);
	Vector3 worldCube2[8];
	Vector3 viewCube2[8];
	Vector3 projectedCube2[8];

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

	bool updateCamara = true;

	float maxForward = 0.5f;
	float currentForward = 0;

	float originalSpeed = 0.2;
	float speed = originalSpeed;

	while (RS_Update(screen.GetSurface(), screen.GetPixels()))
	{
		screen.Fill(black.ARGB);

		Display(screen);

		// Updating Cube

		angle1 += clock.Delta();
		angle2 += clock.Delta() / 2.0f;

		cube1Matrix = Matrix4::Translation(Vector3(0, -0.25f, 0)) * Matrix4::RotationY(angle1);
		cube2Matrix = Matrix4::Translation(Vector3(3.0f, -0.25f, 3.0f)) * Matrix4::RotationZ(angle2) * Matrix4::RotationY(angle1) * Matrix4::Scale(Vector3(2, 2, 2));
		if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
		{
			speed = originalSpeed * 5l;
		}
		else
		{
			speed = originalSpeed;
		}
		if (GetAsyncKeyState('W') & 0x8000 && currentForward < maxForward)
		{
			viewMatrix *= Matrix4::Translation(-viewMatrix.Forward() * speed * clock.Delta());
			currentForward += speed * clock.Delta();
		}
		if (GetAsyncKeyState('S') & 0x8000)
		{
			viewMatrix *= Matrix4::Translation(viewMatrix.Forward() * speed * clock.Delta());
			currentForward -= speed * clock.Delta();
		}
		if (GetAsyncKeyState('D') & 0x8000)
		{
			viewMatrix *= Matrix4::Translation(viewMatrix.Right() * speed * clock.Delta());
		}
		if (GetAsyncKeyState('A') & 0x8000)
		{
			viewMatrix *= Matrix4::Translation(-viewMatrix.Right() * speed * clock.Delta());
		}

		for (int i = 0; i < 8; i++)
		{
			worldCube1[i] = cube1Matrix.TransformPoint(cube1[i]);
			viewCube1[i] = viewMatrix.TransformPoint(worldCube1[i]);
			projectedCube1[i] = projectionMatrix.ProjectPoint(viewCube1[i]);

			worldCube2[i] = cube2Matrix.TransformPoint(cube2[i]);
			viewCube2[i] = viewMatrix.TransformPoint(worldCube2[i]);
			projectedCube2[i] = projectionMatrix.ProjectPoint(viewCube2[i]);
		}

		// Grid

		for (int i = 0; i < 4; i++)
		{
			Vector3 start = projectionMatrix.ProjectPoint(viewMatrix.TransformPoint(Corners[i]));

			Vector3 end = projectionMatrix.ProjectPoint(viewMatrix.TransformPoint(Corners[(i + 1) % 4]));

			screen.LineNx(start.CartesianTo2D(screen), end.CartesianTo2D(screen), gridColor, gridColor);
		}

		for (int i = 0; i < 18; i++)
		{
			Vector3 start = projectionMatrix.ProjectPoint(viewMatrix.TransformPoint(borderVertices[i]));

			Vector3 end = projectionMatrix.ProjectPoint(viewMatrix.TransformPoint(borderVertices[i] + offsetVectors[i % 2]));

			screen.LineNx(start.CartesianTo2D(screen), end.CartesianTo2D(screen), gridColor, gridColor);
		}

		// Cube

		for (int i = 0; i < 8; i++)
		{
			for (int bit = 0; bit < 3; bit++)
			{
				int other = i ^ (1 << bit);

				if (i < other)
				{
					screen.LineNx(projectedCube1[i].CartesianTo2D(screen), projectedCube1[other].CartesianTo2D(screen), cube1Color, cube2Color);
					screen.LineNx(projectedCube2[i].CartesianTo2D(screen), projectedCube2[other].CartesianTo2D(screen), cube2Color, cube1Color);
				}
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