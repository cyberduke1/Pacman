#include "headerfile/Blinky.h"



Blinky::Blinky()
{
    Direction = -1;
    State = CHILLED;
    SpeedX = SLOW;
    SpeedY = SLOW;
    
}

void Blinky::getLocation(point &Point)
{
    Point = Cord;
}

int Blinky::Algorithm(point start,point destination,std::vector<std::string> map)
{
    SecondSearch.BFS(start,destination,map);
}


void Blinky::move(std::vector<std::string> &map) {
    // Get the next position from the BFS algorithm
    point nextPos;
    SecondSearch.getNextMove(nextPos,map);

    // Check if the next position is valid
    if (nextPos.row >= 0 && nextPos.row < map.size() && nextPos.col >= 0 && nextPos.col < map[0].size() && map[nextPos.row][nextPos.col] != '#') {
        // Clear current position
        map[Cord.row][Cord.col] = ' ';
        
        // Update current position
        Cord = nextPos;
        
        // Update map with Blinky's new position
        map[Cord.row][Cord.col] = '0';
    }
}

Blinky::~Blinky()
{
    Direction = -1;
    State = CHILLED;
    SpeedX = SLOW;
    SpeedY = SLOW;
}
