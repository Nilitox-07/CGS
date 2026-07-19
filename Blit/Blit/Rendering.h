#pragma once
#include "Types.h"
#include "NxMath.h"
#include <algorithm>

void DrawTriangle(Vector3 a, Vector3 b, Vector3 c, UINT color, Draw& screen, float* depthBuffer)
{
	Vector2 a2D = a.CartesianTo2D(screen);
	Vector2 b2D = b.CartesianTo2D(screen);
	Vector2 c2D = c.CartesianTo2D(screen);

	float startX = floor(min(a2D.x, min(b2D.x, c2D.x)));
	float endX = ceil(max(a2D.x, max(b2D.x, c2D.x)));

	float startY = floor(min(a2D.y, min(b2D.y, c2D.y)));
	float endY = ceil(max(a2D.y, max(b2D.y, c2D.y)));

	for (int currY = (int)startY; currY < endY; currY++)
	{
		for (int currX = (int)startX; currX < endX; currX++)
		{
			Vector2 currPosition = Vector2(currX, currY);

			Barycentric effect = FindBarycentric(a2D, b2D, c2D, currPosition);

			

			if (effect.alpha >= 0 && effect.alpha <= 1 &&
				effect.beta >= 0 && effect.beta <= 1 &&
				effect.gamma >= 0 && effect.gamma <= 1)
			{
				float depth = effect.alpha * a.z + effect.beta * b.z + effect.gamma * c.z;

				screen.DrawPixel(color, currPosition, depth);
			}
		}
	}
}