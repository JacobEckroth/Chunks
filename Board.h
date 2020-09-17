#pragma once
#include "Chunk.h"
class Board
{
public:
	void render();
	void update();
	void renderChunks(); 
	void updateChunks();
	Board();

	void printTheBoard();
	void clearBoard();

	~Board();
	void deleteChunks();
	void handleMouseDown(SDL_MouseButtonEvent& b);
	void handleMouseUp(SDL_MouseButtonEvent& b);
	void updateMovement(char);
	void init(int, int);
	static float cameraX;
	static float cameraY;
	static int chunkRows;
	static int chunkCols;
	static int boardWidth;
	static int boardHeight;
	

private:

	Chunk** chunks;
	int initialMouseX;
	int initialMouseY;
	char** printBoard;
	bool dragging;
	int xvel;
	int yvel;
	int moveBy;
			//keep track of the top left position of the screen.

};

