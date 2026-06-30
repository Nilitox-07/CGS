#include "Draw.h"

Draw* Draw::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Draw();
	}
	return instance;
}

void Draw::Fill(unsigned int* colorBuffer, const unsigned int color)
{
	
}
