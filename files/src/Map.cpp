#include "Map.h"

#pragma once
Map::Map()
{
}

void Map::DrawCircle(SDL_Renderer *renderer, int32_t centerX, int32_t centerY, int32_t radius)
{
     for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            }
        }
    }
}

void Map::RenderMap(SDL_Renderer* &Renderer) {
    SDL_Rect Draw;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            Draw = {j* CELL_SIZE,i* CELL_SIZE,CELL_SIZE, CELL_SIZE};
                switch (stageOneBoard[i][j]) {
                case '.':
                    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
                    SDL_RenderDrawPoint(Renderer, Draw.x + CELL_SIZE / 2, Draw.y + CELL_SIZE / 2);
                    break;
                case 'o':
                    SDL_SetRenderDrawColor(Renderer, 255, 0, 255, 255);
                    SDL_RenderDrawPoint(Renderer, Draw.x + CELL_SIZE / 2, Draw.y + CELL_SIZE / 2);
                    DrawCircle(Renderer, Draw.x + CELL_SIZE / 2, Draw.y + CELL_SIZE / 2, CELL_SIZE / 6);
                    break;
                case '#':
                    SDL_SetRenderDrawColor(Renderer, 0, 0, 230, 255);
                    SDL_RenderDrawRect(Renderer, &Draw);
                    break;
                case '=':
                    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
                    SDL_RenderFillRect(Renderer, &Draw);
                    break;
                case '1':
                    SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
                    SDL_RenderFillRect(Renderer, &Draw);
                    break;
                case '2':
                    SDL_SetRenderDrawColor(Renderer, 0, 255, 0, 255);
                    SDL_RenderFillRect(Renderer, &Draw);
                    break;
                case '3':
                    SDL_SetRenderDrawColor(Renderer, 0, 0, 255, 255);
                    SDL_RenderFillRect(Renderer, &Draw);
                    break;
                case '4':
                    SDL_SetRenderDrawColor(Renderer, 255, 193, 203, 255);
                    SDL_RenderFillRect(Renderer, &Draw);
                    break;
                }
            }
    }
    SDL_RenderPresent(Renderer);
}

Map::~Map()
{
    return;
}