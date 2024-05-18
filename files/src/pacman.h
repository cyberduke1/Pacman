#ifndef PACMAN_H
#define PACMAN_H
#include "constants.h"

class pacman
{
private:
    
public:
    pacman(SDL_Renderer *renderer);
    SDL_Texture * PacmanSprites;
    SDL_Rect Position;
    std::vector<std::string> Loc;

    std::pair<int,int> getPacmanPos(std::vector<std::string> map);
    enum DIRECTION{
            FIRST_EAST, SECOND_EAST,
            FIRST_WEST, SECOND_WEST,
            FIRST_NORTH, SECOND_NORTH,
            FIRST_SOUTH, SECOND_SOUTH, 
    };
    int Direction;
    SDL_Rect PacmanUpdate(Map &One);
    void PacmanMove(SDL_Event event,Map &One, pacman &Pacman);
    SDL_Texture* LoadSprites(SDL_Renderer *renderer, int rowIndex, int colIndex,std::string pacLocation) const;
    std::vector<std::pair<int,int>> SpriteCord;
    ~pacman();
};


#endif