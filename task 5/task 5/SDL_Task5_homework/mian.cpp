#include "Game.h"
#include <iostream>

using namespace std;


Game* game = NULL;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 640;

int main(int argc, char* argv[]) {

   
    game = new Game();
    game->init("game window task 5",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE);

  
    while (game->isRunning()) {

        game->handleEvents();
        game->update();
        game->render();

    }

   
    game->clean();

    return 0;
}