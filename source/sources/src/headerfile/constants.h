#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <queue>
#include "C:\Users\zulul\Documents\pacman\pacman\source\sources\src\Window.cpp"

#define CELL_SIZE 20
#define LIMIT 21
#define NUM_SPRITES_PER_IMAGE 8
#define FPS 30
#define MEDUIMFPS 40
#define HARDFPS 60
#define FRAME_TARGET_TIME (1000/FPS)
#define MEDIUMFRAME_TARGET_TIME (1000/MEDIUMFPS)
#define HARDFRAME_TARGET_TIME (1000/HARDFPS)
int const WINDOW_HEIGHT = 960;
int const WINDOW_WIDTH = 960;


Window MainWindow;
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
bool quit = false;
SDL_Event e;
int PrevFrameTime = 0;
std::pair<int, int> pacmanPos;
int pacmanX,pacmanY;
