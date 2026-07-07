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
	Draw(const Draw& other);
	~Draw();

	void Fill(const UINT color);
	UINT _2Dto1D(UINT x, UINT y);
	void DrawPixel(const UINT color, Vector2 pos);
	void Blit(Rect sourceRect, Vector2 rasterPos, Draw& image);
	void LoadAnimation(Draw& spriteSheet, Vector2 rasterPos, UINT imageSizeWidth, UINT imageSizeHeight, XTime clock);
	void ParametricLine(Vector2 point1, Vector2 point2, const UINT startColor, const UINT endColor);
	void LineNx(Vector2 point1, Vector2 point2, const UINT startColor, const UINT endColor);

	UINT* GetSurface();
	UINT GetPixels();
	UINT GetWidth();
	UINT GetHeight();
	UINT GetID();
	UINT GetAnimationID();
	Vector2& GetTrack(UINT _animationID, UINT _width, UINT _height, bool step);
	UINT* GetPixel(Vector2 pos);
	void SetImage(UINT* image, UINT _width, UINT _height);
	void Resize(UINT _width, UINT _height);

private:


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

	std::vector<Vector2> runningAnimations;

	bool alphaBlending;

};

