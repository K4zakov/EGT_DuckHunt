#include "Duck.h"
#include <SDL_image.h>
#include <iostream>

#include "Duck.h"

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
    velocityX = 3; // Initial horizontal velocity for bouncing
    velocityY = 3; // Initial vertical velocity for bouncing
    isClicked = false;
}

void Duck::render() {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Duck::update() {
    if (!isClicked) {
        // Bounce around the screen
        rect.x += velocityX;
        rect.y += velocityY;

        // Reverse direction if hitting the screen boundary
        if (rect.x < 0 || rect.x + rect.w > 800) velocityX = -velocityX;
        if (rect.y < 0 || rect.y + rect.h > 600) velocityY = -velocityY;
    }
    else {
        // If clicked, drop to the bottom of the screen
        rect.y += 10; 

        // Stop when reaching the bottom of the screen
        if (rect.y + rect.h >= 600) {
            rect.y = 600 - rect.h;
            velocityY = 0;
            hasHitBottom = true;
            
        }
    }
}

void Duck::handleClick(int mouseX, int mouseY) {
    if (mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y && mouseY <= rect.y + rect.h) {
        isClicked = true;
    }
}

Duck::~Duck() {
    SDL_DestroyTexture(texture);
}