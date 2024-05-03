#include "headerfile/Ghost.h"
#include <SDL2/SDL.h>



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

void Ghost::getPacmanPos(std::vector<std::string> map, point &cord, char m)
{
        for (int row = 0; row < map.size(); row++)
    {
        for (int col = 0; col < map[row].size(); col++)
        {
            if (map[row][col] == m)
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