#include "Game.h"
#include <iostream>


Game::Game() {

	Game::currentQuadrant = -1;
	Game::gameWindow = NULL;
	Game::gameRenderer = NULL;
	Game::running = true;

}


Game::~Game() {
	clean();
}



bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		gameWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (gameWindow != 0)
		{

			gameRenderer = SDL_CreateRenderer(gameWindow, -1, 0);
			if (gameRenderer != 0)
			{

				SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, 255);

				SDL_Surface* tempSurface = SDL_LoadBMP("assets/image.bmp");

				texture = SDL_CreateTextureFromSurface(gameRenderer, tempSurface);

				SDL_FreeSurface(tempSurface);

				SDL_QueryTexture(texture, NULL, NULL, &sourceRectangle.w, &sourceRectangle.h);


				//src rect
				sourceRectangle.x = 0;
				sourceRectangle.y = 0;
				sourceRectangle.w = 225;
				sourceRectangle.h = 225;

				//dest rect
				destinationRectangle.x = 0;
				destinationRectangle.y = 0;
				destinationRectangle.w = 225;
				destinationRectangle.h = 225;

			}
			else {

				return false;

			}
		}
		else {

			return false;

		}
	}
	else {

		return false;

	}

	running = true;
	return true;

}



void Game::render() {
	SDL_RenderClear(gameRenderer);

	
	if (currentQuadrant >= 0) {
		int windowWidth, windowHeight;
		SDL_GetWindowSize(gameWindow, &windowWidth, &windowHeight);

		
		SDL_Rect destRect = destinationRectangle;
		switch (currentQuadrant) {
			//Top Left Quadrant
		case 0:
			destRect.x = 0;
			destRect.y = 0;
			break;
			//Top Right Quadrant
		case 1:
			destRect.x = windowWidth / 2;
			destRect.y = 0;
			break;
			//Bottom Left Quadrant
		case 2:
			destRect.x = 0;
			destRect.y = windowHeight / 2;
			break;
			//Bottom Right Quadrant
		case 3:
			destRect.x = windowWidth / 2;
			destRect.y = windowHeight / 2;
			break;
		}


		SDL_RenderCopy(gameRenderer, texture, NULL, &destRect);
	}

	SDL_RenderPresent(gameRenderer);
}



void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
			int windowWidth, windowHeight;
			SDL_GetWindowSize(gameWindow, &windowWidth, &windowHeight);
			int midX = windowWidth / 2;
			int midY = windowHeight / 2;

			int x = event.button.x;
			int y = event.button.y;
			int quadrant = (x > midX) + (y > midY) * 2;
			currentQuadrant = (currentQuadrant == quadrant) ? -1 : quadrant;
		}
	}
}


void Game::update() {

	
}



void Game::clean() {

	
	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(gameRenderer);
	SDL_Quit();

}


bool Game::isRunning() {

	return Game::running;

}