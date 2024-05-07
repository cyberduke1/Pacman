#ifndef PACMAN_H
#define PACMAN_H
#include "constants.h"

class pacman
{
private:
    std::vector<SDL_Texture *> PacmanSprites;
    void InitPacman(SDL_Renderer *renderer);
    std::string pacLocation;
public:
    pacman(SDL_Renderer *renderer);
    std::pair<int,int> getPacmanPos(std::vector<std::string> map);
    SDL_Texture* LoadSprites(SDL_Renderer *renderer, int rowIndex, int colIndex, int numRows, int numCols);
    ~pacman();
};


#endif