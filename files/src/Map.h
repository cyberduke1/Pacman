#include "pacman.cpp"

#pragma once
class Map
{

public:
    Map();
    void RenderMap(SDL_Renderer* &Renderer);
	void DrawCircle(SDL_Renderer *renderer, int32_t centerX, int32_t centerY, int32_t radius);
    ~Map();
};


