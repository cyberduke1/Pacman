#ifndef PACMAN_H
#define PACMAN_H
#include "constants.h"

class pacman
{
private:
    std::vector<SDL_Texture *> PacmanSprites;
    std::string pacLocation;
public:
    pacman(SDL_Renderer *renderer);
    std::pair<int,int> getPacmanPos(std::vector<std::string> map);
    enum DIRECTION{
            FIRST_WEST, SECOND_WEST,
            FIRST_EAST, SECOND_EAST,
            FIRST_NORTH, SECOND_NORTH,
            FIRST_SOUTH, SECOND_SOUTH, 
    };
    int Direction;
    SDL_Texture* LoadSprites(SDL_Renderer *renderer, int rowIndex, int colIndex, int numRows, int numCols);
    std::vector<std::pair<int,int>> SpriteCord;
    ~pacman();
};


#endif