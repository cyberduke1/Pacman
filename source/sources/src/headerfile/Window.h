#ifndef WINDOW_H
#define WINDOW_H

#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <Windows.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <cmath>


#define CELL_SIZE 40
#define LIMIT 21


using Map = std::vector<std::string>;

class Window {

private:

    void drawFilledCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius);
    bool RenderOnSurface(std::string Location,int x, int y,SDL_Renderer* Render,SDL_Window* windows);
    bool renderFrameOnSurface(std::string Location, int srcX, int srcY, int srcWidth, int srcHeight, int destX, int destY, SDL_Renderer* renderer, SDL_Window* window);
    //void RenderonVector(std::string Location, int srcX, int srcY, int srcWidth, int srcHeight, int destX, int destY,std::vector<SDL_Rect>&Sprite);
    void WindowShown();
    int limit(int window_height);
    void RenderBlinky(int x, int y, SDL_Renderer* Render,SDL_Window* window,int frameIndex);
    void RenderInky(int x, int y, SDL_Renderer* Render,SDL_Window* window);
    void RenderClyde(int x, int y, SDL_Renderer* Render,SDL_Window* window);
    void RenderPinky(int x, int y, SDL_Renderer* Render,SDL_Window* window);
    void RenderPacman(int x, int y, SDL_Renderer* Render,SDL_Window* window);
    //void CollectSpritesFromSheet(const std::string& Location, int spriteWidth, int spriteHeight, std::vector<SDL_Surface*>& sprites);
    
    std::vector<SDL_Rect> BlinkySprites;
    std::vector<SDL_Rect> InkySprites;
    std::vector<SDL_Rect> PinkySprites;
    std::vector<SDL_Rect> ClydeSprites;
    std::vector<SDL_Rect> PacmanSprites;

public:
    int const WINDOW_HEIGHT = 960;
    int const WINDOW_WIDTH = 960;
    int Limit;
    int radius,centerX,centerY;
    SDL_Window* Windows;
    SDL_Surface* WindowSurface;

    //Methods
    SDL_Window* InitializeWindow();
    SDL_Texture* loadTexture(std::string Location, SDL_Renderer* renderer); //    SDL_Texture* newTexture = nullptr;
    bool loadSprite(std::string Location,int width,int height,SDL_Renderer* Render,SDL_Window* window);
    bool DrawMap(SDL_Renderer* renderer,Map map, SDL_Window* window);
    Window();
    ~Window();
};

#endif // WINDOW_H
