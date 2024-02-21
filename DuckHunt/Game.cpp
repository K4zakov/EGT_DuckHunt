//Game.cpp
#include "Game.h"
#include <iostream>
#include "Duck.h"

Duck* duck;



bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags) {

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL init success\n";

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window != 0) //window init success
		{
			std::cout << "window creation success\n";
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
			if (renderer != 0) //renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

				// use the TextureManager to load textures
				/*TextureManager::Instance()->loadTexture("assets/bmp2.bmp", "bmp", renderer);
				TextureManager::Instance()->loadTexture("assets/sprite_sheet_mm_tp.png", "sprite_sheet", renderer);*/
				TextureManager::Instance()->loadTexture("assets/duckhuntbg.png", "png", renderer);
				duck = new Duck(renderer, "assets/duck.png", 320, 240, 100, 100);
			}
			else {
				std::cout << "renderer init failed\n";
				return false;
			}
		}
		else {
			std::cout << "window init failed\n";
			return false;
		}
	}
	else {
		std::cout << "SDL init fail\n";
		return false;
	}

	std::cout << "init success\n";
	running = true;
	return true;
}

void Game::render() {
	
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 255); // sets the window bg color needs to sit before SDL_RenderClear()
	SDL_RenderClear(renderer);
	//TextureManager::Instance()->drawTexture("bmp", 0, 0, 184, 158, renderer, SDL_FLIP_VERTICAL);
	TextureManager::Instance()->drawTexture("png", 0, 0, 800, 600, renderer, SDL_FLIP_NONE);
	
	duck->render();
	

	

	SDL_RenderPresent(renderer);
	
}

void Game::handleEvents() {
	
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);
				duck->handleClick(mouseX, mouseY);
			}
			break;
		default:
			break;
		}
	}
}

void Game::update() {

	duck->update();
	
}

void Game::clean() {
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

bool Game::isRunning() {
	return Game::running;
}

Game::Game() {
	Game::window = NULL;
	Game::renderer = NULL;
	Game::running = true;
	Game::currentFrame = 0;
}

Game::~Game() {

}