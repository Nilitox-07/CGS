#pragma once
#include "Types.h"
#include "Rect.h"
#include "pixels.h"
#include <cstring>
#include <vector>

class Draw
{
public:
	
	static UINT ID_Count;

	Draw(UINT width, UINT height, bool _alphaBlending = true, bool _isAnimation = false, double _animationTimerMax = 60.0f, Draw* _parent = nullptr);
	Draw(Rect imageRect, bool _alphaBlending = true, bool _isAnimation = false, double _animationTimerMax = 60.0f, Draw* _parent = nullptr);
	~Draw();

	void Fill(const UINT color);
	UINT _2Dto1D(UINT x, UINT y);
	void DrawPixel(const UINT color, Point pos);
	void Blit(Rect sourceRect, Point rasterPos, Draw& image);
	void LoadAnimation(Draw& spriteSheet, Point rasterPos, UINT imageSizeWidth, UINT imageSizeHeight, XTime clock);
	void ParametricLine(Point point1, Point point2, const UINT startColor, const UINT endColor);
	void LineNx(Point point1, Point point2, const UINT startColor, const UINT endColor);

	UINT* GetSurface();
	UINT GetPixels();
	UINT GetWidth();
	UINT GetHeight();
	UINT GetID();
	UINT GetAnimationID();
	Point& GetTrack(UINT _animationID, UINT _width, UINT _height, bool step);
	UINT* GetPixel(Point pos);
	void SetImage(UINT* image, UINT _width, UINT _height);
	void Resize(UINT _width, UINT _height);

private:


	Draw(const Draw&) = delete;
	Draw& operator=(const Draw&) = delete;

	UINT numPixels;
	UINT* surface;
	UINT width;
	UINT height;
	
	UINT ID;
	bool isAnimation;
	UINT parentID;
	UINT animationID;
	UINT animationTrack;
	double animationTimer;
	double animationTimerMax;

	std::vector<Point> runningAnimations;

	bool alphaBlending;

};

