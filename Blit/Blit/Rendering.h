#pragma once
#include "Types.h"
#include "NxMath.h"
#include <algorithm>

void DrawTriangle(Vertex a, Vertex b, Vertex c, Draw& material, Draw& screen)
{
	Vector2 a2D = a.position.CartesianTo2D(screen);
	Vector2 b2D = b.position.CartesianTo2D(screen);
	Vector2 c2D = c.position.CartesianTo2D(screen);

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

			Vector2 uvA = (a.uv * effect.alpha);
			Vector2 uvB = (b.uv * effect.beta);
			Vector2 uvC = (c.uv * effect.gamma);

			Vector2 uv = uvA + uvB + uvC;

			int texX = uv.x * (material.GetWidth() - 1);
			int texY = uv.y * (material.GetHeight() - 1);

			if (effect.alpha >= 0 && effect.alpha <= 1 &&
				effect.beta >= 0 && effect.beta <= 1 &&
				effect.gamma >= 0 && effect.gamma <= 1)
			{
				float depth = effect.alpha * a.position.z + effect.beta * b.position.z + effect.gamma * c.position.z;

				int index = material._2Dto1D(texX, texY);

				screen.DrawPixel(material.GetSurface()[index], currPosition, -depth);
			}
		}
	}
}