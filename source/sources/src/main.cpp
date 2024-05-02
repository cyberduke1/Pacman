#include "Window.cpp"
#include <iostream>

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
    Window MainWindow;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *Texture = nullptr;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MainWindow.WINDOW_WIDTH, MainWindow.WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    MainWindow.InitialLoad(renderer);

    // Initial position of Pacman
    int pacmanX = 11; // Column index
    int pacmanY = 7;  // Row index

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
            else if (e.type == SDL_KEYDOWN)
            {
                // Handle key presses to move Pacman
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    if (pacmanY > 0 && map[pacmanY - 1][pacmanX] != '#')
                    {
                        --pacmanY;
                    }
                    break;
                case SDLK_DOWN:
                    if (pacmanY < map.size() - 1 && map[pacmanY + 1][pacmanX] != '#')
                    {
                        ++pacmanY;
                    }
                    break;
                case SDLK_LEFT:
                    if (pacmanX > 0 && map[pacmanY][pacmanX - 1] != '#')
                    {
                        --pacmanX;
                    }
                    break;
                case SDLK_RIGHT:
                    if (pacmanX < map[pacmanY].size() - 1 && map[pacmanY][pacmanX + 1] != '#')
                    {
                        ++pacmanX;
                    }
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        // Update map with Pacman's new position
        map[7] = map[7].substr(0, pacmanX) + '9' + map[7].substr(pacmanX + 1);

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
