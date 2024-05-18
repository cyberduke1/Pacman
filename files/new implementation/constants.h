#ifndef CONSTANTS_H
#define CONSTANTS_H

#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <chrono>
#include <SDL2/SDL_render.h> 
#include <queue>

//constants
#define CELL_SIZE 20
#define LIMIT 21
#define NUM_SPRITES_PER_IMAGE 8
#define FPS 10
#define TARGETFPS 1000/FPS
const int WINDOW_WIDTH = 960;
const int WINDOW_HEIGHT = 960;
int PreviousFrameTime = 0;
const int TARGET_FPS = 30;
float DeltaTime = 0;
const int FRAME_DELAY = 1000 / TARGET_FPS;
const float PacmanSpeed = 100.0f;
using Map = std::vector<std::string>;


#endif //CONSTANTS_H