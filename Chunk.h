#pragma once
#include "SDL.h"
class Chunk
{
public:
	static int chunkPixelWidth;
	static int chunkPixelHeight;
	void init(int,int);
	void render();
	void update(int,int);
	void updateColor();
private:
	int row;
	int r;
	int g;
	int b;
	int rvel, gvel, bvel;
	int col;
	int xPos;
	int yPos;
	SDL_Rect drawRect;



};

