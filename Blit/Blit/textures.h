#pragma once
#include "tiles_12.h"
#include <vector>
#include "pixels.h"

void ConvertBGRAtoARGB(UINT* texture, UINT textureWidth, UINT totalPixels)
{
	std::vector<Pixels> _texture;
	_texture.reserve(totalPixels);
	_texture.assign(texture, texture + totalPixels);
	for (int textureIndex = 0; textureIndex < totalPixels; textureIndex++)
	{
		texture[textureIndex] = _texture[textureIndex].ARGB;
	}
}

void ConvertImages()
{
	ConvertBGRAtoARGB(tiles_12_pixels, tiles_12_width, tiles_12_numpixels);
}