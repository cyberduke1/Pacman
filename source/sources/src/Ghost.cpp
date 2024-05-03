#include "headerfile/Ghost.h"
#include <SDL2/SDL.h>
#include "Ghost.h"


Ghost::~Ghost()
{
    Direction = 0;
    State = 0;
    SpeedX = 0;
    SpeedY = 0;
}
Ghost::Ghost()
{
    Direction = -1;
    State = -1;
    SpeedX = 0;
    SpeedY = 0;
}

int Ghost::Algorithm(point start,point destination,std::vector<std::string> map)
{
    getPacmanPos(map,start);

    FirstSearch.BFS(start,destination,map);
}

void Ghost::getPacmanPos(std::vector<std::string> map, point &cord)
{
        for (int row = 0; row < map.size(); row++)
    {
        for (int col = 0; col < map[row].size(); col++)
        {
            if (map[row][col] == '9')
            {
                cord = {row, col};
            }
        }
    }
    
}

int Ghost::Change_State()
{
    return 0;
}