#pragma once
class Draw
{
private:

	static Draw* instance;

	Draw();

public:

	static Draw* GetInstance();
	void Fill(unsigned int* colorBuffer, const unsigned int color);
};

