#pragma once
class Draw
{
public:

	static Draw& GetInstance();

	void Fill(unsigned int* colorBuffer, const unsigned int color, const unsigned int numPixels);

private:

	Draw();

	Draw(const Draw&) = delete;
	Draw& operator=(const Draw&) = delete;

};

