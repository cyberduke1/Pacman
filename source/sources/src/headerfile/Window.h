#ifndef WINDOW_H
#define WINDOW_H

#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define CELL_SIZE 20
#define LIMIT 21
#define NUM_SPRITES_PER_IMAGE 8

using Map = std::vector<std::string>;

class Window
{

private:
    SDL_Texture* LoadSprite(const std::string &location, SDL_Renderer *renderer, int spriteIndex);
    SDL_Texture* LoadSprites(const std::string &location, SDL_Renderer *renderer, int rowIndex, int colIndex, int numRows, int numCols);
    void DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius);
    std::vector<std::string> Located;

    std::vector<SDL_Texture *> BlinkySprites;
    std::vector<SDL_Texture *> InkySprites;
    std::vector<SDL_Texture *> PinkySprites;
    std::vector<SDL_Texture *> ClydeSprites;
    std::vector<SDL_Texture *> PacmanSprites;

public:
    int const WINDOW_HEIGHT = 960;
    int const WINDOW_WIDTH = 960;

    //Methods
    void InitialLoad(SDL_Renderer *renderer);
    bool DrawMap(SDL_Renderer *renderer, Map map);
    Window();
    ~Window();
};

#endif // WINDOW_H