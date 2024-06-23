#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
#include <iostream>
#include <string>
#include <string.h>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <chrono>

//constants
#define CELL_SIZE 25
#define NUM_SPRITES_PER_IMAGE 8
#define WIDTH 29
#define HEIGHT 35
const int WINDOW_WIDTH = 960;
const int WINDOW_HEIGHT = 960;
using Maps = std::vector<std::string>;
using namespace std;

    string stageOneBoard[35] =
	{"                            "
	"                            ",
	"                            ",
	"############################",
	"#............##............#",
	"#.####.#####.##.#####.####.#",
	"#o####.#####.##.#####.####o#",
	"#.####.#####.##.#####.####.#",
	"#..........................#",
	"#.####.##.########.##.####.#",
	"#.####.##.########.##.####.#",
	"#......##....##....##......#",
	"######.##### ## #####.######",
	"     #.##### ## #####.#     ",
	"     #.##### ## #####.#     ",
	"     #.##    1     ##.#     ",
	"######.## ###==### ##.######",
	"&     .   #     ##  .     @",
	"######.## #2 3 4## ##.######",
	"     #.## ######## ##.#     ",
	"######.## ######## ##.######",
	"######.##   'a'    ##.######",
	"######.## ######## ##.######",
	"#............##............#",
	"#.####.#####.##.#####.####.#",
	"#.####.#####.##.#####.####.#",
	"#o..##.......9........##..o#",
	"###.##.##.########.##.##.###",
	"###.##.##.########.##.##.###",
	"#......##....##....##......#",
	"#.##########.##.##########.#",
	"#.##########.##.##########.#",
	"#..........................#",
	"############################",
	"                            ",
	"                            "};



#endif //CONSTANTS_H