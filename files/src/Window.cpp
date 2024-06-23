#include "window.h"

window::window(SDL_Renderer* &Renderer, SDL_Window* &Window) {
    StartWindow(Renderer, Window);
}

void window::StartWindow(SDL_Renderer* &MainRenderer, SDL_Window* &MainWindow) {
    MainWindow = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (MainWindow == nullptr) {
        std::cout << "Could not create an instance of the window, SDL_WINDOW_ERROR: " << SDL_GetError() << std::endl;
        return;
    }

    MainRenderer = SDL_CreateRenderer(MainWindow, -1, SDL_RENDERER_ACCELERATED);

    if (MainRenderer == nullptr) {
        std::cout << "Could not create an instance of SDL_Renderer, SDL_RENDERER_ERROR: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_SetRenderDrawColor(MainRenderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(MainRenderer);
    SDL_RenderPresent(MainRenderer);
    SDL_Delay(20);
}

void window::Screen() {
    SDL_Event event;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }
}

std::pair<int, int> window::GetPacmanPos() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (stageOneBoard[i][j] == '9') {
                return {j * CELL_SIZE, i * CELL_SIZE};
            }
        }
    }
    return {-1, -1};
}

void window::ResetPositions(pacman &Pacman, Blinky &Blinky, Inky &Inky) {
    
    stageOneBoard[Pacman.PacmanRect.y / CELL_SIZE][Pacman.PacmanRect.x / CELL_SIZE] = ' ';
    Pacman.PacmanRect.x = initialPacmanPosX;
    Pacman.PacmanRect.y = initialPacmanPosY;
    stageOneBoard[Pacman.PacmanRect.y / CELL_SIZE][Pacman.PacmanRect.x / CELL_SIZE] = '9';

    
    std::pair<int, int> BlinkyPos = Blinky.GetBlinkyPos();
    stageOneBoard[BlinkyPos.first][BlinkyPos.second] = ' ';
    stageOneBoard[initialBlinkyPosY][initialBlinkyPosX] = '1';

    // Reset Inky's position
    std::pair<int, int> InkyPos = Inky.GetInkyPos();
    stageOneBoard[InkyPos.first][InkyPos.second] = ' ';
    stageOneBoard[initialInkyPosY][initialInkyPosX] = '2';
}

bool window::CheckCollision(pacman &Pacman, Blinky &Blinky, Inky &Inky) {
    std::pair<int, int> pacmanPos = Pacman.GetPacmanPos();
    std::pair<int, int> blinkyPos = Blinky.GetBlinkyPos();
    std::pair<int, int> inkyPos = Inky.GetInkyPos();

    if ((pacmanPos.first == blinkyPos.first && pacmanPos.second == blinkyPos.second) ||
        (pacmanPos.first == inkyPos.first && pacmanPos.second == inkyPos.second)) {
        return true;
    }
    return false;
}

void window::Screen(SDL_Renderer* &Renderer, Map &map, Blinky &Blinky, Inky &Inky,Pinky &pinky, pacman &Pacman) {
    SDL_Event event;
    bool quit = false;
    std::pair<int, int> Pacs;
    Pacs = GetPacmanPos();
    Pacman.PacmanRect.x = Pacs.first;
    Pacman.PacmanRect.y = Pacs.second;
    
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        Pacman.setDirection(UP);
                        break;
                    case SDLK_DOWN:
                        Pacman.setDirection(DOWN);
                        break;
                    case SDLK_LEFT:
                        Pacman.setDirection(LEFT);
                        break;
                    case SDLK_RIGHT:
                        Pacman.setDirection(RIGHT);
                        break;
                }
            }
        }
        SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
        SDL_RenderClear(Renderer);
    
        Pacman.move();
        Blinky.move(Pacman);
        Inky.move(Pacman);
        pinky.move(Pacman);
        
        if (CheckCollision(Pacman, Blinky, Inky)) {
            ResetPositions(Pacman, Blinky, Inky);
        }

        Pacman.RenderPacman(Renderer);
        map.RenderMap(Renderer);
        SDL_RenderPresent(Renderer);
        SDL_Delay(120);
    }
}

void window::close(SDL_Renderer *&Renderer, SDL_Window *&Window) {
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

window::~window() {}
