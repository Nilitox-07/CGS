#pragma once
#include <vector>
#include "Draw.h"
#include "tiles_12.h"
#include "pixels.h"
#include "fire_02.h"

Draw ConvertBGRAtoARGB(const UINT* texture, UINT textureWidth, UINT totalPixels)
{
	std::vector<Pixels> _texture;
	Draw image(Rect(textureWidth, totalPixels), true);
	_texture.reserve(totalPixels);
	_texture.assign(texture, texture + totalPixels);
	for (int textureIndex = 0; textureIndex < totalPixels; textureIndex++)
	{
		image.DrawPixel(_texture[textureIndex].ARGB, Point(textureIndex, 0));
	}
	return image;
}

void ConvertImages()
{
	ConvertBGRAtoARGB(tiles_12_pixels, tiles_12_width, tiles_12_numpixels);
	ConvertBGRAtoARGB(fire_02_pixels, fire_02_width, fire_02_numpixels);
}