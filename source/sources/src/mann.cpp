#include "Window.cpp"
#include <iostream>
#include <utility>

std::pair<int,int> getPacmanPos(std::vector<std::string> map);

std::vector<std::string> map = {
    " ################### ",
    " #........#........# ",
    " #o##.###.#.###.##o# ",
    " #.................# ",
    " #.##.#.#####.#.##.# ",
    " #....#...#...#....# ",
    " ####.### # ###.#### ",
    "    #.#   0   #.#    ",
    "#####.# ##=## #.#####",
    "     .  #123#  .     ",
    "#####.# ##### #.#####",
    "    #.#       #.#    ",
    " ####.# ##### #.#### ",
    " #........#........# ",
    " #.##.###.#.###.##.# ",
    " #o.#.....9.....#.o# ",
    " ##.#.#.#####.#.#.## ",
    " #....#...#...#....# ",
    " #.######.#.######.# ",
    " #.................# ",
    " ################### "
};

int main(int argc, char *argv[])
{

    MainWindow.InitialLoad(renderer);

    // Initial position of Pacman
    std::pair<int,int> pacmanPos = getPacmanPos(map);
    int pacmanX = pacmanPos.second; 
    int pacmanY = pacmanPos.first;

    bool quit = false;
    SDL_Event e;

    const int FPS = 60;
    const int frameDelay = 1000 / FPS; // in milliseconds
    Uint32 frameStart;
    int frameTime;

    
    return 0;
}

std::pair<int,int> getPacmanPos(std::vector<std::string> map)
{
    for (int row = 0; row < map.size(); row++)
    {
        for (int col = 0; col < map[row].size(); col++)
        {
            if (map[row][col] == '9')
            {
                return {row, col};
            }
        }
    }
    return {-1, -1}; // Pacman not found
}
