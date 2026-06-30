#include "Draw.h"

Draw::Draw()
{

}

Draw& Draw::GetInstance()
{
	static Draw instance;
	return instance;
}

void Draw::Fill(unsigned int* colorBuffer, const unsigned int color, const unsigned int numPixels)
{
	for (unsigned int* currentPtr = colorBuffer; currentPtr != colorBuffer + numPixels; currentPtr++)
	{
		*currentPtr = color;
	}
}
