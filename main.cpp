#include "Window.h"
#include "SDL.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <ctime>
#include <crtdbg.h>
#include <iostream>
int main() {
	srand(time(NULL));
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	int frames = 0;
	Uint32 lastSaidFrames;
	Window* gameWindow = new Window;
	int windowWidth = 800;
	int windowHeight = 800;
	gameWindow->init("Zooming", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, false);
	while (gameWindow->running()) {
		/*if (frames == 0) {


			lastSaidFrames = SDL_GetTicks();
		}*/
		frameStart = SDL_GetTicks();
		gameWindow->handleEvents();
		gameWindow->update();
		gameWindow->render();
		frameTime = SDL_GetTicks() - frameStart;
		/*frames++;
		if (SDL_GetTicks() - lastSaidFrames >= 1000) {
			lastSaidFrames = SDL_GetTicks();
			std::cout << "FPS:" << frames << std::endl;
			frames = 0;
		}*/
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	gameWindow->clean();
	delete gameWindow;




	_CrtDumpMemoryLeaks();
	return 0;
}