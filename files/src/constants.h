#ifndef CONSTANTS_H
#define CONSTANTS_H

#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h> 
#include <queue>

//constants
#define CELL_SIZE 20
#define LIMIT 21
#define NUM_SPRITES_PER_IMAGE 8
#define FPS 30
#define TARGETFPS 1000/FPS
const int WINDOW_WIDTH = 960;
const int WINDOW_HEIGHT = 960;
int PreviousFrameTime = 0;



#endif //CONSTANTS_H