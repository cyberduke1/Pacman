#include "Window.cpp"
#include <iostream>
#include <utility>

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
    " ################### "
};

enum DIRECTION {
    FIRST_SOUTH,
    SECOND_SOUTH,
    FIRST_EAST,
    SECOND_EAST,
    FIRST_NORTH,
    SECOND_NORTH,
    FIRST_WEST,
    SECOND_WEST
};

void Init();
void EventListener();

int main(int argc, char *argv[])
{
    Init();

    while (!quit)
    {
        EventListener();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        map[pacmanY][pacmanX] = '9'; // Update Pacman position

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
    return {-1, -1}; // Pacman not found
}

void Init(){

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,WINDOW_WIDTH,WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    MainWindow.InitialLoad(renderer);

    pacmanPos = getPacmanPos(map);
    pacmanX = pacmanPos.second;
    pacmanY = pacmanPos.first;
}

void EventListener()
{
        float deltaTime = (SDL_GetTicks() - PrevFrameTime) / 1000.0;
        PrevFrameTime = SDL_GetTicks();

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    if (pacmanY > 0 && map[pacmanY - 1][pacmanX] != '#' && map[pacmanY - 1][pacmanX] != '='  && map[pacmanY - 1][pacmanX] != '0'  && map[pacmanY - 1][pacmanX] != '1' && map[pacmanY - 1][pacmanX] != '2' && map[pacmanY - 1][pacmanX] != '3')
                    {
                        map[pacmanY][pacmanX] = ' '; // Clear previous position
                        --pacmanY;
                    }
                    break;
                case SDLK_DOWN:
                    if (pacmanY < map.size() - 1 && map[pacmanY + 1][pacmanX] != '#' && map[pacmanY + 1][pacmanX] != '=' && map[pacmanY + 1][pacmanX] != '0'  && map[pacmanY + 1][pacmanX] != '1' && map[pacmanY + 1][pacmanX] != '2'  && map[pacmanY + 1][pacmanX] != '3')
                    {
                        map[pacmanY][pacmanX] = ' '; // Clear previous position
                        ++pacmanY;
                    }
                    break;
                case SDLK_LEFT:
                    if (pacmanX > 0 && map[pacmanY][pacmanX - 1] != '#' && map[pacmanY][pacmanX - 1] != '=' &&map[pacmanY][pacmanX - 1] != '0' && map[pacmanY][pacmanX - 1] != '1' && map[pacmanY][pacmanX - 1] != '2' && map[pacmanY][pacmanX - 1] != '3')
                    {
                        map[pacmanY][pacmanX] = ' '; // Clear previous position
                        --pacmanX;
                    }
                    break;
                case SDLK_RIGHT:
                    if (pacmanX < map[pacmanY].size() - 1 && map[pacmanY][pacmanX + 1] != '#' && map[pacmanY][pacmanX + 1] != '=' && map[pacmanY][pacmanX + 1] != '0' && map[pacmanY][pacmanX + 1] != '1' && map[pacmanY][pacmanX + 1] != '2' && map[pacmanY][pacmanX + 1] != '3')
                    {
                        map[pacmanY][pacmanX] = ' '; // Clear previous position
                        ++pacmanX;
                    }
                    break;
            }
        }
    }
}
