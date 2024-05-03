#ifndef BLINKY_H
#define BLINKY_H

#include "C:\Users\zulul\Documents\pacman\Pacman\source\sources\src\Ghost.cpp"

class Blinky : Ghost {
    public:
        node SecondSearch;
        int Algorithm(point start,point destination,std::vector<std::string> map);
        Blinky(); //Exact location of the pacman
        void getLocation(point &c);
        void move(std::vector<std::string> &map); // Function to move Blinky
        point Cord;
        ~Blinky();
};

#endif