#include "Chunk.h"
#include "Board.h"
#include "Window.h"
#include <iostream>
#include <cmath>
int Chunk::chunkPixelWidth = 0;
int Chunk::chunkPixelHeight = 0;
void Chunk::render() {
	SDL_SetRenderDrawColor(Window::renderer,r,g,b,255);
	SDL_RenderFillRect(Window::renderer, &drawRect);
}

void Chunk::update(int wrapAroundRow,int wrapAroundCol) {
	//std::cout << "chunk row and col, and wrap around row and col" << row << " " << col << " " << wrapAroundRow << " " << wrapAroundCol << std::endl;
	if (row == 0 && wrapAroundRow < 0) {
		wrapAroundRow++;
	}
	if (col == 0 && wrapAroundCol < 0) {
		wrapAroundCol++;
	}
	drawRect.x = xPos + ((wrapAroundCol)*Board::boardWidth) - Board::cameraX;
	
	drawRect.y = yPos + ((wrapAroundRow)*Board::boardWidth)- Board::cameraY;
	updateColor();
	
}

void Chunk::updateColor() {

	r += 1 * rvel;
	if (r > 255) {
		r = 255;
		rvel = -1;
	}
	else if (r < 0) {
		r = 0;
		rvel = 1;
	}
	g += 2 * gvel;
	if (g > 255) {
		g = 255;
		gvel = -1;
	}
	else if (g < 0) {
		g = 0;
		gvel = 1;
	}
	b += 3* bvel;
	if (b > 255) {
		b = 255;
		bvel = -1;
	}
	else if (b < 0) {
		b = 0;
		bvel = 1;
	}

}

void Chunk::init(int setRow, int setCol) {
	row = setRow;
	col = setCol;
	xPos = col * chunkPixelWidth;
	yPos = row * chunkPixelHeight;
	drawRect.x = xPos;
	drawRect.y = yPos;
	drawRect.w = chunkPixelWidth;
	drawRect.h = chunkPixelHeight;
	bvel = 1;
	gvel = 1;
	rvel = -1;
	r = rand() % 256;
	g = rand() % 256;
	b =  rand() % 256;
	
	
}
