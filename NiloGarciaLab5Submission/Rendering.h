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

			Vector3 uvA = (a.uvw * effect.alpha);
			Vector3 uvB = (b.uvw * effect.beta);
			Vector3 uvC = (c.uvw * effect.gamma);

			Vector3 uvw = uvA + uvB + uvC;

			int texX = uvw.x * (material.GetWidth() - 1);
			int texY = uvw.y * (material.GetHeight() - 1);

			if (effect.alpha >= 0 && effect.alpha <= 1 &&
				effect.beta >= 0 && effect.beta <= 1 &&
				effect.gamma >= 0 && effect.gamma <= 1)
			{
				float depth = effect.alpha * a.position.z + effect.beta * b.position.z + effect.gamma * c.position.z;

				int index = material._2Dto1D(texX, texY);

				Vector3 colorA = Vector3(a.color.red, a.color.green, a.color.blue);
				Vector3 colorB = Vector3(b.color.red, b.color.green, b.color.blue);
				Vector3 colorC = Vector3(c.color.red, c.color.green, c.color.blue);

				float red = colorA.x * effect.alpha + colorB.x * effect.beta + colorC.x * effect.gamma;
				float green = colorA.y * effect.alpha + colorB.y * effect.beta + colorC.y * effect.gamma;
				float blue = colorA.z * effect.alpha + colorB.z * effect.beta + colorC.z * effect.gamma;

				Pixels finalColorCalculated;

				finalColorCalculated.red = red;
				finalColorCalculated.green = green;
				finalColorCalculated.blue = blue;
				finalColorCalculated.alpha = 255;

				finalColorCalculated.ARGB_Func();

				Pixels finalColor(material.GetSurface()[index], true);
				finalColor *= finalColorCalculated;

				screen.DrawPixel(finalColor.ARGB, currPosition, -depth);
			}
		}
	}
}