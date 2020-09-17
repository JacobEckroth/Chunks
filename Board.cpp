#include "Board.h"
#include "Window.h"
#include <iostream>

int Board::chunkRows = 0;
int Board::chunkCols = 0;
float Board::cameraX = 0;
float Board::cameraY = 0;
int Board::boardWidth = 0;
int Board::boardHeight = 0;

void Board::render() {
	renderChunks();


}

Board::~Board() {
	deleteChunks();
}


void Board::deleteChunks() {
	for (int i = 0; i < chunkRows; i++) {
		delete[] chunks[i];
		delete[] printBoard[i];
	}
	delete[] chunks;
	delete[] printBoard;
}




void Board::handleMouseDown(SDL_MouseButtonEvent& button) {
	dragging = true;
	int x, y;
	if (button.button == SDL_BUTTON_LEFT) {
		SDL_GetMouseState(&x, &y);
		initialMouseX = x;
		initialMouseY = y;
	}
	else {
		SDL_GetMouseState(&x, &y);
		std::cout << "Mouse is at X:" << x << " Y:" << y << std::endl;
		dragging = false;
	}
}
void Board::handleMouseUp(SDL_MouseButtonEvent& b) {
	initialMouseX = -1;
	initialMouseY = -1;
	dragging = false;
}

Board::Board() {
	dragging = false;
}

void Board::updateMovement(char newMove) {
	switch (newMove) {
	case 'l':
		xvel -= 1;
		break;
	case 'r':
		xvel += 1;
		break;
	case 'u':
		yvel -= 1;
		break;
	case 'd':
		yvel += 1;
		break;
	case ' ':
		yvel = 0;
		xvel = 0;
		break;
	}
}
void Board::renderChunks() {
	int rightBound = cameraX + Window::screenWidth;
	int bottomBound = cameraY + Window::screenHeight;
	int topBound = cameraY;
	int leftBound = cameraX;	//setting the bounds for the pixels we'll draw
	int firstChunkCol = leftBound / Chunk::chunkPixelWidth;	//CALCULATes the beginning of the search
	int firstChunkRow = topBound / Chunk::chunkPixelHeight;

	bool increasingCol = true;
	bool increasingRow = true;
	firstChunkRow-=1; //shift to the left so we don't miss the left side or the top which might be
						//partially off screen
	firstChunkCol-=1;
	int chunkCol = firstChunkCol;
	int chunkRow = firstChunkRow;

	while (increasingRow) {
		while (increasingCol) {
	
			int actualChunkRow = chunkRow % chunkRows;

			int actualChunkCol = chunkCol % chunkCols;
		
			if (chunkRow < 0) {
				actualChunkRow = (chunkRows - abs((chunkRow % chunkRows))) % chunkRows;				//THIS IS WRONGGGGGGG
				
		
			}
			if (chunkCol < 0) {
				actualChunkCol = (chunkCols - abs((chunkCol % chunkCols))) % chunkCols;
			
				
			}
		
			//SDL_Delay(50);
			printBoard[actualChunkRow][actualChunkCol] = 'f';
			chunks[actualChunkRow][actualChunkCol].render();
			chunkCol++;
			if (chunkCol * Chunk::chunkPixelWidth > rightBound) {
				increasingCol = false;
			}
		}
		increasingCol = true;
		chunkCol = firstChunkCol;
		chunkRow++;

		if (chunkRow * Chunk::chunkPixelHeight > bottomBound) {
			
			increasingRow = false;
		}
	}
	//printTheBoard();
}

void Board::printTheBoard() {
	for (int i = 0; i < chunkRows; i++) {
		for (int j = 0; j < chunkCols; j++) {
			std::cout << printBoard[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Board::update() {

	clearBoard();
	if (dragging) {
		int newY, newX;
		SDL_GetMouseState(&newX, &newY);
		cameraX -= (newX - initialMouseX);
		cameraY -= (newY - initialMouseY);
		initialMouseX = newX;
		initialMouseY = newY;
	}


	cameraX += xvel * moveBy;
	cameraY += yvel * moveBy;
	updateChunks();
	
}


void Board::clearBoard() {
	for (int i = 0; i < chunkRows; i++) {
		for (int j = 0; j < chunkCols; j++) {
			printBoard[i][j] = 'e';
		}
	}
}
void Board::updateChunks() {
	int rightBound = cameraX + Window::screenWidth;
	int bottomBound = cameraY + Window::screenHeight;
	int topBound = cameraY;
	int leftBound = cameraX;
	int firstChunkCol = leftBound / Chunk::chunkPixelWidth;
	int firstChunkRow = topBound / Chunk::chunkPixelHeight;

	bool increasingCol = true;
	bool increasingRow = true;
	firstChunkRow-=1;
	firstChunkCol-=1;
	int chunkCol = firstChunkCol;
	int chunkRow = firstChunkRow;

	
				//shift to the left so we don't miss the left side or the top
	while (increasingRow) {
		while (increasingCol) {
			int wrapAroundCol = chunkCol / chunkCols;	//how many times we wrap around
			int wrapAroundRow = chunkRow / chunkRows;
			int actualChunkRow = chunkRow % chunkRows;
			
			int actualChunkCol = chunkCol % chunkCols;
			if (chunkRow < 0) {
				actualChunkRow = (chunkRows - abs((chunkRow % chunkRows))) % chunkRows;				//THIS IS WRONGGGGGGG
				//std::cout << "Actual chunk row being drawn is:" << actualChunkRow << std::endl;;
				wrapAroundRow -= 1;	//minus one, because we gotta offset
			}
			if (chunkCol < 0) {
				actualChunkCol = (chunkCols - abs((chunkCol%chunkCols))) % chunkCols;
			// std::cout << "Actual chunk col being drawn is:" << actualChunkCol << std::endl;
				wrapAroundCol -= 1;	//gotta offest
			}
		
			chunks[actualChunkRow][actualChunkCol].update(wrapAroundRow,wrapAroundCol);
			chunkCol++;
			if (chunkCol * Chunk::chunkPixelWidth > rightBound) {	//checks if the top left of a square would excede the right bound
				increasingCol = false;
			}
		}
		increasingCol = true;
		chunkCol = firstChunkCol;
		chunkRow++;

		if (chunkRow * Chunk::chunkPixelHeight > bottomBound) {

			increasingRow = false;
		}
	}
}

void Board::init(int newRows, int newCols) {
	chunkRows = newRows;
	chunkCols = newCols;
	Chunk::chunkPixelWidth = Chunk::chunkPixelHeight = 10;
	chunks = new Chunk * [newRows];
	for (int i = 0; i < newRows; i++) {
		chunks[i] = new Chunk[newCols];
	}
	for (int i = 0; i < newRows; i++) {
		for (int j = 0; j < newCols; j++) {
			chunks[i][j].init(i, j);
		}
	}
	printBoard = new char* [newRows];
	for (int i = 0; i < newRows; i++) {
		printBoard[i] = new char[newCols];
	}

	boardHeight = chunkRows * Chunk::chunkPixelHeight;
	boardWidth = chunkCols * Chunk::chunkPixelWidth;
	moveBy = 1;
}