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
    Window MainWindow;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *Texture = nullptr;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MainWindow.WINDOW_WIDTH, MainWindow.WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    MainWindow.InitialLoad(renderer);

    // Initial position of Pacman
    std::pair<int,int> pacmanPos = getPacmanPos(map);
    int pacmanX = pacmanPos.second; 
    int pacmanY = pacmanPos.first;

    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            map[pacmanY] = map[pacmanY].substr(0, pacmanX) + '9' + map[pacmanY].substr(pacmanX + 1);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
        
        
            map[pacmanY] = map[pacmanY].substr(0, pacmanX) + '9' + map[pacmanY].substr(pacmanX + 1);

            if (!MainWindow.DrawMap(renderer, map))
            {
                break;
            }
            SDL_RenderPresent(renderer);


            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    if (pacmanY > 0 && map[pacmanY - 1][pacmanX] != '#' && map[pacmanY - 1][pacmanX] != '=')
                    {
                        
                        if (map[pacmanY][pacmanX] == '.')
                            map[pacmanY] = map[pacmanY].substr(0, pacmanX) + '.' + map[pacmanY].substr(pacmanX + 1);
                        else
                            map[pacmanY] = map[pacmanY].substr(0, pacmanX) + ' ' + map[pacmanY].substr(pacmanX + 1);
                        --pacmanY;
                    }
                    break;
                case SDLK_DOWN:
                    if (pacmanY < map.size() - 1 && map[pacmanY + 1][pacmanX] != '#' && map[pacmanY + 1][pacmanX] != '=')
                    {
                        
                        if (map[pacmanY][pacmanX] == '.')
                            map[pacmanY] = map[pacmanY].substr(0, pacmanX) + '.' + map[pacmanY].substr(pacmanX + 1);
                        else
                            map[pacmanY] = map[pacmanY].substr(0, pacmanX) + ' ' + map[pacmanY].substr(pacmanX + 1);
                        ++pacmanY;
                    }
                    break;
                case SDLK_LEFT:
                    if (pacmanX > 0 && map[pacmanY][pacmanX - 1] != '#' && map[pacmanY][pacmanX - 1] != '=')
                    {
                        
                        if (map[pacmanY][pacmanX] == '.')
                            map[pacmanY] = map[pacmanY].substr(0, pacmanX) + '.' + map[pacmanY].substr(pacmanX + 1);
                        else
                            map[pacmanY] = map[pacmanY].substr(0, pacmanX) + ' ' + map[pacmanY].substr(pacmanX + 1);
                        --pacmanX;
                    }
                    break;
                case SDLK_RIGHT:
                    if (pacmanX < map[pacmanY].size() - 1 && map[pacmanY][pacmanX + 1] != '#' && map[pacmanY][pacmanX + 1] != '=')
                    {
                        
                        if (map[pacmanY][pacmanX] == '.')
                            map[pacmanY] = map[pacmanY].substr(0, pacmanX) + '.' + map[pacmanY].substr(pacmanX + 1);
                        else
                            map[pacmanY] = map[pacmanY].substr(0, pacmanX) + ' ' + map[pacmanY].substr(pacmanX + 1);
                        ++pacmanX;
                    }
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        
        map[pacmanY] = map[pacmanY].substr(0, pacmanX) + '9' + map[pacmanY].substr(pacmanX + 1);

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

