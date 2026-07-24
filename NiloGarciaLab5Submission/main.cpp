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
#include "StoneHenge.h"

void Display(Draw& screen);
void GenerateStars(Vertex*& starList, int amount);

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

	RS_Initialize("Nilo Garcia: Lab 5", width, height);
	Draw screen(width, height, Draw::NEEDS_DEPTH);

	std::vector<Pixels> colors = { red, green, blue, yellow, purple, cyan };

	Pixels backgroundColor = Pixels(0xFF003366, true);

	// Material/Textures

	std::vector<Draw> materials;

	for (int currColor = 0; currColor < colors.size(); currColor++)
	{
		materials.push_back(Draw(256, 256));
		materials[currColor].Fill(colors[currColor].ARGB);
	}

	// Loading Stars

	Vertex* stars = nullptr;
	int starAmount = 3000;

	GenerateStars(stars, starAmount);

	// Loading Stone Hedges Object

	int numVerts = 1457;

	Vertex* stoneEdgesInfo = new Vertex[numVerts];

	for (int i = 0; i < numVerts; i++)
	{
		Vector3 position = Vector3(StoneHenge_data[i].pos[0], StoneHenge_data[i].pos[1], StoneHenge_data[i].pos[2]);
		position = position * 0.1f;

		position.y *= -1;

		Vector3 uvw = Vector3(StoneHenge_data[i].uvw[0], StoneHenge_data[i].uvw[1], StoneHenge_data[i].uvw[2]);
		Vector3 norm = Vector3(StoneHenge_data[i].nrm[0], StoneHenge_data[i].nrm[1], StoneHenge_data[i].nrm[2]);

		Vertex vert(position, uvw, norm);

		stoneEdgesInfo[i] = vert;
	}

	// Camara

	Matrix4 cameraMatrix = Matrix4::Indentity();

	cameraMatrix *= Matrix4::RotationX(-18 * std::numbers::pi_v<float> / 180.0f);
	cameraMatrix *= Matrix4::Translation(Vector3(0, 0, -4));

	Matrix4 viewMatrix = cameraMatrix.Inverse();

	// Projection

	float aspect = (float)screen.GetWidth() / screen.GetHeight();

	Matrix4 projectionMatrix = Matrix4::Perspective(90.0f * std::numbers::pi_v<float> / 180.0f, aspect, 0.1f, 10.0f);

	float yaw = 0;
	float pitch = 0;

	float sens = 25.0f;

	// Light

	Vector3 lightDir = Vector3(-0.577, 0.577, -0.577);
	Pixels lightColor = Pixels(0xFFC0C0F0, true);

	Vector3 pointLightPosition = Vector3(-1, 0.5, -1);
	//Pixels pointLightColor = Pixels(0, true);
	Pixels pointLightColor = Pixels(0xFFFFFF00, true);

	float pulseMax = 10.0f;
	float pulseMin = 0.0f;

	float pulseRate = 1.0f;

	while (RS_Update(screen.GetSurface(), screen.GetPixels()))
	{
		// Refresh Screen

		screen.Fill(backgroundColor.ARGB);
		screen.ClearDepthBuffer();

		// Moving Camara

		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			pitch -= sens * clock.Delta();
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			pitch += sens * clock.Delta();
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			yaw += sens * clock.Delta();
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			yaw -= sens * clock.Delta();
		}


		Matrix4 cameraMatrix = Matrix4::Indentity();

		cameraMatrix *= Matrix4::RotationX(yaw * std::numbers::pi_v<float> / 180.0f) * Matrix4::RotationY(pitch * std::numbers::pi_v<float> / 180.0f);
		cameraMatrix *= Matrix4::Translation(Vector3(0, 0, -4));

		Matrix4 viewMatrix = cameraMatrix.Inverse();

		// Rendering Stars

		for (int starNum = 0; starNum < starAmount; starNum++)
		{
			Vector3 viewStar = viewMatrix.TransformPoint(stars[starNum].position);
			Vector3 projectedStar = projectionMatrix.ProjectPoint(viewStar);

			float tol = 0.1f;

			if (projectedStar.x < -1.0f - tol || projectedStar.x > 1.0f + tol ||
				projectedStar.y < -1.0f - tol || projectedStar.y > 1.0f + tol ||
				projectedStar.z < -1.0f - tol || projectedStar.z > 1.0f + tol)
			{
				continue;
			}

			Vector2 screenPosition = projectedStar.CartesianTo2D(screen);

			screen.DrawPixel(white.ARGB, screenPosition, -1);
		}

		// Updating Vertices

		Vertex* updatedVerts = new Vertex[numVerts];

		for (int i = 0; i < numVerts; i++)
		{
			Vector3 viewVertice = viewMatrix.TransformPoint(stoneEdgesInfo[i].position);
			Vector3 projectedVertice = projectionMatrix.ProjectPoint(viewVertice);

			Vector3 normView = viewMatrix.TransformPoint(stoneEdgesInfo[i].norm);
			Vector3 normProj = projectionMatrix.TransformPoint(stoneEdgesInfo[i].norm);
		
			float ambiant = 0.2f;

			float dirRatio = stoneEdgesInfo[i].norm.Normalize().Dot(lightDir) + ambiant;
			Clamp(dirRatio);

			Pixels dirBlack = black;
			dirBlack.Lerp(lightColor, dirRatio);

			float pulseRatio = (0.5f * (1.0f + sinf((float)clock.TotalTime() * pulseRate)));

			float lightRange = 25.0f;

			Vector3 lightDirection = pointLightPosition - stoneEdgesInfo[i].position;
			float magnitude = lightDirection.MagnitudeSquared();
			float distancedRatio = 1.0f - ClampVal(magnitude / lightRange);

			Pixels pointBlack = black;
			pointBlack.Lerp(pointLightColor, ClampVal(stoneEdgesInfo[i].norm.Normalize().Dot(lightDirection.Normalize()) * pulseRatio * distancedRatio));


			dirBlack += pointBlack;

			updatedVerts[i] = Vertex(projectedVertice, stoneEdgesInfo[i].uvw, normProj);

			updatedVerts[i].color = dirBlack;
		}

		// Rendering Objects

		for (int i = 0; i < 2532; i += 3)
		{
			Vertex a = updatedVerts[StoneHenge_indicies[i]];
			Vertex b = updatedVerts[StoneHenge_indicies[i + 1]];
			Vertex c = updatedVerts[StoneHenge_indicies[i + 2]];

			//float facing = a.norm.Dot(viewMatrix.Forward());

			//if (facing > 0)
			//	continue;

			DrawTriangle(a, b, c, stoneTexture, screen);
		}

		// Clear Memory

		delete[] updatedVerts;

		// Clock/Frame Update

		clock.Signal();
	}

	RS_Shutdown();

	if (stars != nullptr)
	{
		delete[] stars;
		stars = nullptr;
	}

	return 0;
}

void Display(Draw& screen)
{
}

void GenerateStars(Vertex*& starList, int amount)
{
	if (starList != nullptr)
	{
		delete[] starList;
		starList = nullptr;
	}

	starList = new Vertex[amount];

	for (int i = 0; i < amount; i++)
	{
		float x = (rand() - (RAND_MAX / 2.0f)) / (RAND_MAX / 2.0f);
		float y = (rand() - (RAND_MAX / 2.0f)) / (RAND_MAX / 2.0f);
		float z = (rand() - (RAND_MAX / 2.0f)) / (RAND_MAX / 2.0f);

		Vector3 position(x, y, z);
		position.Normalize();

		position = position * 50.0f;

		Vertex info(position, Vector3(), Vector3());

		starList[i] = info;
	}
}