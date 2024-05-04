#ifndef GHOST_H
#define GHOST_H
#include <string>

#include "C:\Users\zulul\Documents\pacman\pacman\source\sources\src\bfs.cpp"


class Ghost{

public:
    Ghost();
    int Direction;
    int State;
    int SpeedX;
    int SpeedY;
    int PosX,PosY;
    point start,destination;
    std::string ImgLoc;
    enum DIRECTION{FIRST_SOUTH,SECOND_SOUTH,FIRST_EAST,SECOND_EAST,FIRST_NORTH,SECOND_NORTH,FIRST_WEST,SECOND_WEST}; //first and second entries are used to choose the eyes for the sprite at the time
    enum STATE{CHILLED,ANGRY,PISSED};
    enum SPEED{SLOW,MEDIUM,FAST};
    void getPacmanPos(std::vector<std::string> map, point &cord,char m);
    ~Ghost();
private:
    int Change_State();
};

#endif