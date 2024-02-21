#pragma once
#include <SDL.h>


class Duck {
public:
    Duck(SDL_Renderer* renderer, const char* imagePath, int x, int y, int width, int height);
    ~Duck();
    void update();
    void render();
    void handleClick(int mouseX, int mouseY);

private:
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    SDL_Rect rect;
    int velocityX;
    int velocityY;
};

