#pragma once
#include "Types.h"
#include "pixels.h"
#include <cstring>
#include <vector>

struct Vector2;
struct Rect;

class Draw
{
public:
	
	static UINT ID_Count;
	static char ALPHA_BLENDING;
	static char IS_ANIMATION;
	static char NEEDS_DEPTH;

	Draw();
	Draw(UINT width, UINT height, char _flags = 0b00000000);
	Draw(Rect imageRect, char _flags = 0b00000000);
	Draw(const Draw& other);
	Draw& operator=(const Draw& other);
	~Draw();

	void Fill(const UINT color);
	UINT _2Dto1D(UINT x, UINT y);
	void DrawPixel(const UINT color, Vector2 pos, float depth);
	void Blit(Rect sourceRect, Vector2 rasterPos, Draw& image, float depth);
	void LoadAnimation(Draw& spriteSheet, Vector2 rasterPos, UINT imageSizeWidth, UINT imageSizeHeight, XTime clock, float depth);
	void ParametricLine(Vector2 point1, Vector2 point2, const UINT startColor, const UINT endColor, float depth);
	void LineNx(Vector2 point1, Vector2 point2, const UINT startColor, const UINT endColor, float depth);

	UINT* GetSurface();
	UINT GetPixels();
	UINT GetWidth() const;
	UINT GetHeight() const;
	UINT GetID();
	UINT GetAnimationID();
	float* GetDepthBuffer();
	Vector2& GetTrack(UINT _animationID, UINT _width, UINT _height, bool step);
	UINT* GetPixel(Vector2 pos);
	void SetImage(UINT* image, UINT _width, UINT _height);
	void Resize(UINT _width, UINT _height);
	void SetAnimationTimer(double _animationTimerMax, Draw* _parent);
	void ClearDepthBuffer();
	void TurnOnDepth();
	void TurnOffDepth();

	static int _2Dto1D(UINT x, UINT y, UINT width);

private:

	UINT numPixels;
	UINT* surface;
	UINT width;
	UINT height;
	float* depthBuffer = nullptr;
	
	char flags = 0b00000000;

	UINT ID = 0;
	UINT parentID = 0;
	UINT animationID = 0;
	UINT animationTrack = 0;
	double animationTimer = 0;
	double animationTimerMax = 0;

	std::vector<Vector2> runningAnimations;

};

