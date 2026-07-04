#include "Draw.h"
#include <iostream>

UINT Draw::ID_Count = 0;

Draw::Draw(UINT _width, UINT _height, bool _alphaBlending, bool _isAnimation, double _animationTimerMax, Draw* _parent) :
	width(_width),
	height(_height),
	numPixels(_width* _height),
	surface(new UINT[numPixels]),
	alphaBlending(_alphaBlending),
	ID(0),
	isAnimation(_isAnimation),
	parentID(0),
	animationID(0),
	animationTrack(0),
	animationTimer(_animationTimerMax),
	animationTimerMax(_animationTimerMax)
{
	Draw::ID_Count++;
	ID = Draw::ID_Count;
	if (_isAnimation)
	{
		parentID = _parent->GetID();
		animationID = _parent->GetAnimationID();
	}
}

Draw::Draw(Rect imageRect, bool _alphaBlending, bool _isAnimation, double _animationTimerMax, Draw* _parent) :
	width(imageRect.width),
	height(imageRect.height),
	numPixels(imageRect.width* imageRect.height),
	surface(new UINT[numPixels]),
	alphaBlending(_alphaBlending),
	ID(0),
	isAnimation(_isAnimation),
	parentID(0),
	animationID(0),
	animationTrack(0),
	animationTimer(_animationTimerMax),
	animationTimerMax(_animationTimerMax)
{
	Draw::ID_Count++;
	ID = Draw::ID_Count;
	if (_isAnimation)
	{
		parentID = _parent->GetID();
		animationID = _parent->GetAnimationID();
	}
}

Draw::~Draw()
{
	delete[] surface;
}

UINT* Draw::GetSurface()
{
	return surface;
}

UINT Draw::GetPixels()
{
	return numPixels;
}

UINT Draw::GetWidth()
{
	return width;
}

UINT Draw::GetHeight()
{
	return height;
}

UINT Draw::GetID()
{
	return ID;
}

UINT Draw::GetAnimationID()
{
	runningAnimations.push_back(Point());
	return runningAnimations.size() - 1;
}

Point& Draw::GetTrack(UINT _animationID, UINT _width, UINT _height, bool step)
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

UINT* Draw::GetPixel(Point pos)
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

void Draw::DrawPixel(const UINT color, Point pos)
{
	surface[_2Dto1D((int)pos.x, (int)pos.y)] = color;
}

void Draw::Blit(Rect sourceRect, Point rasterPos, Draw& image)
{
	if (alphaBlending && image.alphaBlending)
	{
		for (int y = 0; y < sourceRect.height && y + rasterPos.y < height; y++)
		{
			for (int x = 0; x < sourceRect.width && x + rasterPos.x < width; x++)
			{
				Pixels destination(*GetPixel(Point(x + rasterPos.x, y + rasterPos.y)), true);
				Pixels source(*image.GetPixel(Point(x + sourceRect.pos.x, y + sourceRect.pos.y)), true);
				
				destination.Lerp(source);
				DrawPixel(destination.ARGB, Point(x + rasterPos.x, y + rasterPos.y));
			}
		}
	}
	else
	{
		const UINT* imagePtr = image.GetPixel(sourceRect.pos);

		for (UINT* bufferPtr = GetPixel(rasterPos); bufferPtr < surface + numPixels && imagePtr < image.surface + image.numPixels; bufferPtr += width)
		{
			std::memcpy(bufferPtr, imagePtr, sourceRect.width * sizeof(UINT));
			imagePtr += image.width;
			if (sourceRect.width > width)
				std::cout << "ROW OVERFLOW RISK\n";

			if (sourceRect.pos.x + sourceRect.width > image.width)
				std::cout << "SOURCE READ OVERFLOW\n";

			if ((bufferPtr + sourceRect.width) > (surface + numPixels))
				std::cout << "DEST WRITE OVERFLOW\n";
		}
	}
}

void Draw::LoadAnimation(Draw& spriteSheet, Point rasterPos, UINT imageSizeWidth, UINT imageSizeHeight, XTime clock)
{
	if (spriteSheet.isAnimation && spriteSheet.parentID == ID)
	{
		spriteSheet.animationTimer += clock.Delta();
		if (spriteSheet.animationTimer >= 1 / spriteSheet.animationTimerMax)
		{
			Point& animationTrackCur = GetTrack(spriteSheet.animationID, spriteSheet.GetWidth() / imageSizeWidth, spriteSheet.GetHeight() / imageSizeHeight, true);
			Blit(Rect(imageSizeWidth, imageSizeHeight, Point(animationTrackCur.x * imageSizeWidth, animationTrackCur.y * imageSizeHeight)), rasterPos, spriteSheet);
			spriteSheet.animationTimer = 0;
		}
		else
		{
			Point& animationTrackCur = GetTrack(spriteSheet.animationID, spriteSheet.GetWidth() / imageSizeWidth, spriteSheet.GetHeight() / imageSizeHeight, false);
			Blit(Rect(imageSizeWidth, imageSizeHeight, Point(animationTrackCur.x * imageSizeWidth, animationTrackCur.y * imageSizeHeight)), rasterPos, spriteSheet);
		}
	}
}

void Draw::LineNx(const UINT color, Point point1, Point point2)
{
	if (point1.x == point2.x)
	{
		for (int y = fmin(point1.y, point2.y); y < fmin(point1.y, point2.y) + fabs(point1.y - point2.y); y++)
		{
			DrawPixel(color, Point(point1.x, y));
		}
		return;
	}
	float slope = (point2.y - point1.y) / (point2.x - point1.x);
	float intercept = point1.y - slope * point1.x;
	if (fabs(point1.x - point2.x) >= fabs(point1.y - point2.y))
	{
		for (int x = fmin(point1.x, point2.x); x < fmin(point1.x, point2.x) + fabs(point1.x - point2.x); x++)
		{
			DrawPixel(color, Point(x, slope * x + intercept));
		}
	}
	else
	{
		for (int y = fmin(point1.y, point2.y); y < fmin(point1.y, point2.y) + fabs(point1.y - point2.y); y++)
		{
			DrawPixel(color, Point((y - intercept)/slope, y));
		}
	}
}