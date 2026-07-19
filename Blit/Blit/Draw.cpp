#include "Draw.h"
#include <iostream>
#include "NxMath.h"

UINT Draw::ID_Count = 0;

char Draw::ALPHA_BLENDING = 0b00000001;
char Draw::IS_ANIMATION = 0b00000010;
char Draw::NEEDS_DEPTH = 0b00000100;

Draw::Draw(UINT _width, UINT _height, char _flags) :
	width(_width),
	height(_height),
	numPixels(_width* _height),
	surface(new UINT[numPixels]),
	flags(_flags)
{
	Draw::ID_Count++;
	ID = Draw::ID_Count;
	if (flags & NEEDS_DEPTH)
	{
		depthBuffer = new float[width * height];
	}
}

Draw::Draw(Rect imageRect, char _flags) :
	width(imageRect.width),
	height(imageRect.height),
	numPixels(imageRect.width* imageRect.height),
	surface(new UINT[numPixels]),
	flags(_flags)
{
	Draw::ID_Count++;
	ID = Draw::ID_Count;
	
}

Draw::Draw(const Draw& other) :
	width(other.width),
	height(other.height),
	numPixels(other.width* other.height),
	surface(new UINT[numPixels]),
	flags(other.flags)
{
	memcpy(surface, other.surface, numPixels);
	Draw::ID_Count++;
	ID = Draw::ID_Count;
}

Draw::~Draw()
{
	delete[] surface;
	if (flags & NEEDS_DEPTH)
		delete[] depthBuffer;
}

UINT* Draw::GetSurface()
{
	return surface;
}

UINT Draw::GetPixels()
{
	return numPixels;
}

UINT Draw::GetWidth() const
{
	return width;
}

UINT Draw::GetHeight() const
{
	return height;
}

UINT Draw::GetID()
{
	return ID;
}

UINT Draw::GetAnimationID()
{
	runningAnimations.push_back(Vector2());
	return runningAnimations.size() - 1;
}

float* Draw::GetDepthBuffer()
{
	return depthBuffer;
}

Vector2& Draw::GetTrack(UINT _animationID, UINT _width, UINT _height, bool step)
{
	// TODO: insert return statement here

	//for (int y = 0; y < spriteSheet.GetHeight() / imageSizeHeight; y++)
	//{
	//	for (int x = 0; x < spriteSheet.GetWidth() / imageSizeWidth; x++)
	//	{
	//	}
	//}
	if (!step)
		return runningAnimations[_animationID];

	runningAnimations[_animationID].x++;
	if (runningAnimations[_animationID].x >= _width)
	{
		runningAnimations[_animationID].x = 0;
		runningAnimations[_animationID].y++;
		if (runningAnimations[_animationID].y >= _height)
		{
			runningAnimations[_animationID].y = 0;
		}
	}

	return runningAnimations[_animationID];
}

UINT* Draw::GetPixel(Vector2 pos)
{
	return &surface[_2Dto1D((int)pos.x, (int)pos.y)];
}

void Draw::SetImage(UINT* image, UINT _width, UINT _height)
{
	Resize(_width, _height);

	std::memcpy(surface, image, numPixels * sizeof(*surface));
}

void Draw::Resize(UINT _width, UINT _height)
{
	if (surface != nullptr)
	{
		delete[] surface;
		surface = nullptr;
	}

	width = _width;
	height = _height;
	numPixels = width * height;

	surface = new UINT[numPixels];
}

void Draw::SetAnimationTimer(double _animationTimerMax, Draw* _parent)
{
	if (flags & IS_ANIMATION)
	{
		parentID = _parent->GetID();
		animationID = _parent->GetAnimationID();
	}
}

void Draw::ClearDepthBuffer()
{
	if (flags & NEEDS_DEPTH)
		for (int i = 0; i < width * height; i++)
		{
			depthBuffer[i] = FLT_MAX;
		}
}

void Draw::TurnOnDepth()
{
	if (flags & NEEDS_DEPTH)
		return;
	else
	{
		flags |= NEEDS_DEPTH;
		
		depthBuffer = new float[width * height];

		ClearDepthBuffer();
	}
}

void Draw::TurnOffDepth()
{
	if (flags & NEEDS_DEPTH)
	{
		flags &= ~NEEDS_DEPTH;
		delete[] depthBuffer;
		depthBuffer = nullptr;
	}
}

int Draw::_2Dto1D(UINT x, UINT y, UINT width)
{
	return x + y * width;
}


void Draw::Fill(const UINT color)
{
	for (unsigned int* currentPtr = surface; currentPtr != surface + numPixels; currentPtr++)
	{
		*currentPtr = color;
	}
}

UINT Draw::_2Dto1D(UINT x, UINT y)
{
	return x + y * width;
}

void Draw::DrawPixel(const UINT color, Vector2 pos, float depth)
{
	if (pos.x >= width || pos.x < 0 || pos.y >= height || pos.y < 0)
		return;
	int index = _2Dto1D(std::floor(pos.x), std::floor(pos.y));
	if (flags & NEEDS_DEPTH)
	{

		if (depth >= depthBuffer[index])
			return;
		depthBuffer[index] = depth;
	}
	surface[index] = color;
}

void Draw::Blit(Rect sourceRect, Vector2 rasterPos, Draw& image, float depth)
{
	if (flags & ALPHA_BLENDING && image.flags & ALPHA_BLENDING)
	{
		for (int y = 0; y < sourceRect.height && y + rasterPos.y < height; y++)
		{
			for (int x = 0; x < sourceRect.width && x + rasterPos.x < width; x++)
			{
				Pixels destination(*GetPixel(Vector2(x + rasterPos.x, y + rasterPos.y)), true);
				Pixels source(*image.GetPixel(Vector2(x + sourceRect.pos.x, y + sourceRect.pos.y)), true);
				
				destination.Lerp(source);
				DrawPixel(destination.ARGB, Vector2(x + rasterPos.x, y + rasterPos.y), depth);
			}
		}
	}
	else
	{
		const UINT* imagePtr = image.GetPixel(sourceRect.pos);

		for (UINT* bufferPtr = GetPixel(rasterPos); bufferPtr < surface + numPixels && imagePtr < image.surface + image.numPixels; bufferPtr += width)
		{
			int posibleSubstraction = (int)rasterPos.x + (int)sourceRect.width - (int)width;
			std::memcpy(bufferPtr, imagePtr, ((int)sourceRect.width - (posibleSubstraction > 0 ? posibleSubstraction : 0)) * sizeof(UINT));
			imagePtr += image.width;
		}
	}
}

void Draw::LoadAnimation(Draw& spriteSheet, Vector2 rasterPos, UINT imageSizeWidth, UINT imageSizeHeight, XTime clock, float depth)
{
	if (spriteSheet.flags & IS_ANIMATION && spriteSheet.parentID == ID)
	{
		spriteSheet.animationTimer += clock.Delta();
		if (spriteSheet.animationTimer >= 1 / spriteSheet.animationTimerMax)
		{
			Vector2& animationTrackCur = GetTrack(spriteSheet.animationID, spriteSheet.GetWidth() / imageSizeWidth, spriteSheet.GetHeight() / imageSizeHeight, true);
			Blit(Rect(imageSizeWidth, imageSizeHeight, Vector2(animationTrackCur.x * imageSizeWidth, animationTrackCur.y * imageSizeHeight)), rasterPos, spriteSheet, depth);
			spriteSheet.animationTimer = 0;
		}
		else
		{
			Vector2& animationTrackCur = GetTrack(spriteSheet.animationID, spriteSheet.GetWidth() / imageSizeWidth, spriteSheet.GetHeight() / imageSizeHeight, false);
			Blit(Rect(imageSizeWidth, imageSizeHeight, Vector2(animationTrackCur.x * imageSizeWidth, animationTrackCur.y * imageSizeHeight)), rasterPos, spriteSheet, depth);
		}
	}
}

void Draw::ParametricLine(Vector2 point1, Vector2 point2, const UINT startColor, const UINT endColor, float depth)
{
	if (point1.x == point2.x)
	{
		for (int y = fmin(point1.y, point2.y); y < fmin(point1.y, point2.y) + fabs(point1.y - point2.y); y++)
		{
			Pixels color(startColor, true);
			Pixels maxColor(endColor, true);
			color.Lerp(maxColor, (y - fmin(point1.y, point2.y)) / fabs(point1.y - point2.y));
			DrawPixel(color.ARGB, Vector2(point1.x, y), depth);
		}
		return;
	}
	else if (point1.y == point2.y)
	{
		for (int x = fmin(point1.x, point2.x); x < fmin(point1.x, point2.x) + fabs(point1.x - point2.x); x++)
		{
			Pixels color(startColor, true);
			Pixels maxColor(endColor, true);
			color.Lerp(maxColor, (x - fmin(point1.x, point2.x)) / fabs(point1.x - point2.x));
			DrawPixel(color.ARGB, Vector2(x, point1.y), depth);
		}
		return;
	}
	if (fabs(point1.x - point2.x) >= fabs(point1.y - point2.y))
	{
		for (int x = fmin(point1.x, point2.x); x < fmin(point1.x, point2.x) + fabs(point1.x - point2.x); x++)
		{
			float ratio = (x - fmin(point1.x, point2.x)) / (fabs(point1.x - point2.x));
			
			float y = std::lerp((fmin(point1.x, point2.x) == point1.x ? point1.y : point2.y), (fmin(point1.x, point2.x) == point2.x ? point1.y : point2.y), ratio);

			Pixels color(startColor, true);
			Pixels maxColor(endColor, true);
			color.Lerp(maxColor, (y - fmin(point1.y, point2.y)) / fabs(point1.y - point2.y));
			DrawPixel(color.ARGB, Vector2(x, std::floor(y + 0.5)), depth);
		}
	}
	else
	{
		for (int y = fmin(point1.y, point2.y); y < fmin(point1.y, point2.y) + fabs(point1.y - point2.y); y++)
		{
			float ratio = (y - fmin(point1.y, point2.y)) / (fabs(point1.y - point2.y));

			float x = std::lerp((fmin(point1.y, point2.y) == point1.y ? point1.x : point2.x), (fmin(point1.y, point2.y) == point2.y ? point1.x : point2.x), ratio);

			Pixels color(startColor, true);
			Pixels maxColor(endColor, true);
			color.Lerp(maxColor, (x - fmin(point1.x, point2.x)) / fabs(point1.x - point2.x));
			DrawPixel(color.ARGB, Vector2(std::floor(x + 0.5), y), depth);
		}
	}
}

void Draw::LineNx(Vector2 point1, Vector2 point2, const UINT startColor, const UINT endColor, float depth)
{
	if (point1.x == point2.x)
	{
		for (int y = fmin(point1.y, point2.y); y < fmin(point1.y, point2.y) + fabs(point1.y - point2.y); y++)
		{
			Pixels color(startColor, true);
			Pixels maxColor(endColor, true);
			color.Lerp(maxColor, (y - fmin(point1.y, point2.y)) / fabs(point1.y - point2.y));
			DrawPixel(color.ARGB, Vector2(point1.x, y), depth);
		}
		return;
	}
	float slope = (point2.y - point1.y) / (point2.x - point1.x);
	float intercept = point1.y - slope * point1.x;
	if (fabs(point1.x - point2.x) >= fabs(point1.y - point2.y))
	{
		for (int x = fmin(point1.x, point2.x); x < fmin(point1.x, point2.x) + fabs(point1.x - point2.x); x++)
		{
			Pixels color(startColor, true);
			Pixels maxColor(endColor, true);
			color.Lerp(maxColor, (x - fmin(point1.x, point2.x)) / fabs(point1.x - point2.x));
			DrawPixel(color.ARGB, Vector2(x, slope * x + intercept), depth);
		}
	}
	else
	{
		for (int y = fmin(point1.y, point2.y); y < fmin(point1.y, point2.y) + fabs(point1.y - point2.y); y++)
		{
			Pixels color(startColor, true);
			Pixels maxColor(endColor, true);
			color.Lerp(maxColor, (y - fmin(point1.y, point2.y)) / fabs(point1.y - point2.y));
			DrawPixel(color.ARGB, Vector2((y - intercept)/slope, y), depth);
		}
	}
}