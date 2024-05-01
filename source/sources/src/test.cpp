#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SPRITE_WIDTH = 32; // Width of each sprite frame
const int SPRITE_HEIGHT = 32; // Height of each sprite frame

void WindowShown() {
    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;
        }
    }
}

int main(int argc, char* args[]) {
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    std::string path = "C:\\Users\\zulul\\Documents\\pacman\\Pacman\\source\\resources\\sprites\\blinky.png";
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cout << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Surface* windowSurface = SDL_GetWindowSurface(window);
    if (windowSurface == nullptr) {
        std::cout << "Unable to get window surface! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(loadedSurface);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* spriteSheet = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    SDL_Rect srcRect; // Rect representing the position and size of the sprite frame within the sprite sheet
    srcRect.x = 0; // X-coordinate of the top-left corner of the sprite frame in the sprite sheet
    srcRect.y = 0; // Y-coordinate of the top-left corner of the sprite frame in the sprite sheet
    srcRect.w = SPRITE_WIDTH; // Width of the sprite frame
    srcRect.h = SPRITE_HEIGHT; // Height of the sprite frame

    SDL_Rect destRect; // Rect representing the position and size of the sprite on the window
    destRect.x = (SCREEN_WIDTH - SPRITE_WIDTH) / 2; // X-coordinate of the top-left corner of the sprite on the window
    destRect.y = (SCREEN_HEIGHT - SPRITE_HEIGHT) / 2; // Y-coordinate of the top-left corner of the sprite on the window
    destRect.w = SPRITE_WIDTH; // Width of the sprite on the window
    destRect.h = SPRITE_HEIGHT; // Height of the sprite on the window

    SDL_RenderCopy(renderer, spriteSheet, &srcRect, &destRect);
    SDL_RenderPresent(renderer);

    WindowShown();

    SDL_DestroyTexture(spriteSheet);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
