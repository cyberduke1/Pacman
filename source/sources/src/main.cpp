#include "Window.cpp"
#include <iostream>
#include <utility>
#include "C:\Users\zulul\Documents\pacman\pacman\source\sources\src\blinky.cpp"

std::pair<int, int> getPacmanPos(std::vector<std::string> map);

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
    " ################### "};

int main(int argc, char *argv[])
{
    Window MainWindow;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *Texture = nullptr;
    Blinky Red;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MainWindow.WINDOW_WIDTH, MainWindow.WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    MainWindow.InitialLoad(renderer);

    // Initial position of Pacman
    std::pair<int, int> pacmanPos = getPacmanPos(map);
    point Destination = {pacmanPos.second, pacmanPos.first};
    int pacmanX = pacmanPos.second;
    int pacmanY = pacmanPos.first;
    point BlinkPos;
    Red.getLocation(BlinkPos);
    Red.SecondSearch.BFS(BlinkPos, Destination, map);

    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {

            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        // Move Blinky
        point currentBlinkPos;
        Red.getLocation(currentBlinkPos);
        if (currentBlinkPos != Destination)
        {
            Red.SecondSearch.BFS(currentBlinkPos, Destination, map);
            Red.move(map); // Assuming you have a move function in your Blinky class
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        map[currentBlinkPos.row][currentBlinkPos.col] = ' '; // Clear previous position
        map[Destination.row][Destination.col] = '9';        // Update destination position

        if (!MainWindow.DrawMap(renderer, map))
        {
            break;
        }
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

std::pair<int, int> getPacmanPos(std::vector<std::string> map)
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
}

