#pragma once
#include <vector>
#include "Draw.h"
#include "tiles_12.h"
#include "pixels.h"
#include "fire_02.h"
#include "NxMath.h"
#include "celestial.h"
#include "flower.h"
#include "greendragon.h"
#include "treeolife.h"

Draw tile;
Draw fire;
Draw flower;
Draw celestial;
Draw dragon;
Draw tree;

Draw ConvertBGRAtoARGB(const UINT* texture, UINT textureWidth, UINT textureHeight, UINT totalPixels)
{
	std::vector<Pixels> _texture;
	Draw image(Rect(textureWidth, textureHeight), Draw::ALPHA_BLENDING);
	_texture.reserve(totalPixels);
	_texture.assign(texture, texture + totalPixels);
	for (int textureIndex = 0; textureIndex < totalPixels; textureIndex++)
	{
		int x = textureIndex % textureWidth;
		int y = textureIndex / textureWidth;

		image.DrawPixel(_texture[textureIndex].ARGB, Vector2(x, y), 1);
	}
	return image;
}

void ConvertImages()
{
	tile = ConvertBGRAtoARGB(tiles_12_pixels, tiles_12_width, tiles_12_height, tiles_12_numpixels);
	fire = ConvertBGRAtoARGB(fire_02_pixels, fire_02_width, fire_02_height, fire_02_numpixels);
	flower = ConvertBGRAtoARGB(flower_pixels, flower_width, flower_height, flower_numpixels);
	celestial = ConvertBGRAtoARGB(celestial_pixels, celestial_width, celestial_height, celestial_numpixels);
	dragon = ConvertBGRAtoARGB(greendragon_pixels, greendragon_width, greendragon_height, greendragon_numpixels);
	tree = ConvertBGRAtoARGB(treeolife_pixels, treeolife_width, treeolife_height, treeolife_numpixels);
}