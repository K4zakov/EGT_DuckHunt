#include "Duck.h"
#include <SDL_image.h>
#include <iostream>

Duck::Duck(SDL_Renderer* renderer, const char* imagePath, int x, int y, int width, int height) {
    this->renderer = renderer;
    SDL_Surface* surface = IMG_Load(imagePath);
    if (surface == NULL) {
        std::cerr << "Unable to load image! SDL Error: " << SDL_GetError() << std::endl;
        return;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    rect = { x, y, width, height };
    velocityX = 3;
    velocityY = 3;
}
void Duck::render() {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
void Duck::update() {
    rect.x += velocityX;
    rect.y += velocityY;

    if (rect.x < 0 || rect.x + rect.w > 800)
        velocityX = -velocityX;
    if (rect.y < 0 || rect.y + rect.h > 600)
        velocityY = -velocityY;
}

void Duck::handleClick(int mouseX, int mouseY) {
    // Check if the mouse click is within the bird's rectangle
    if (mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y && mouseY <= rect.y + rect.h) {
        // Move the bird down by a certain amount when clicked
        rect.y += 1000;  
    }
}