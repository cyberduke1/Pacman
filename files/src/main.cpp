#include "pacman.cpp"
#include "Window.cpp"

SDL_Window *GameWindow = nullptr;
SDL_Renderer *MainRenderer = nullptr;
SDL_Event event;

void Init();
void DrawMap(SDL_Renderer *renderer, Map One, pacman Pacman, Window LoadMap, int Spritenum);
int HandlePacmanMovement(pacman& Pacman, Map& UpdatedState,int index,float DeltaTime);
void PrintMap(Map &One){
    for(auto one : One){
        for(auto in : one){
            std::cout<<in<<" ";
        }
        std::cout<<"\n";
    }
}

bool CheckWall(Map UpdatedState,pacman Pacman){
    int pacmanY = Pacman.getPacmanPos(UpdatedState).first;
    int pacmanX = Pacman.getPacmanPos(UpdatedState).second;

     switch (Pacman.Direction) {
        case Pacman.FIRST_SOUTH:
        case Pacman.SECOND_SOUTH:
            if (pacmanY < UpdatedState.size() - 1 && UpdatedState[pacmanY + 1][pacmanX] != '#') {
                return true;
            }
            break;
        case Pacman.FIRST_EAST:
        case Pacman.SECOND_EAST:
            if (pacmanX < UpdatedState[pacmanY].size() - 1 && UpdatedState[pacmanY][pacmanX + 1] != '#') {
                return true;
            }
            break;
        case Pacman.FIRST_NORTH:
        case Pacman.SECOND_NORTH:
            if (pacmanY > 0 && UpdatedState[pacmanY - 1][pacmanX] != '#') {
                return true;
            }
            break;
        case Pacman.FIRST_WEST:
        case Pacman.SECOND_WEST:
            if (pacmanX > 0 && UpdatedState[pacmanY][pacmanX - 1] != '#') {
                return true;
            }
            break;
        default:
            break;
    }
    return false;
}

void delay(){
    Uint32 elapsedTime = SDL_GetTicks() - PreviousFrameTime;
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), TARGETFPS+PreviousFrameTime));
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), TARGETFPS+PreviousFrameTime));
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), TARGETFPS+PreviousFrameTime));
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), TARGETFPS+PreviousFrameTime));
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), TARGETFPS+PreviousFrameTime));
    PreviousFrameTime = SDL_GetTicks();
}

int main(int argc, char* argv[]) {
    Init();

    pacman Pacman(MainRenderer);
    Window LoadMaps;
    bool quit = false;
    int nextSprite = 1;
    int CurrentStage = 1;
    int CurrentState = 1;
    float DeltaTime = 0;
    Map UpdatedState = LoadMaps.Stages(CurrentStage);

    DrawMap(MainRenderer, UpdatedState, Pacman, LoadMaps, nextSprite);
    SDL_RenderPresent(MainRenderer);

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {

            while(!SDL_TICKS_PASSED(SDL_GetTicks(),PreviousFrameTime+FRAME_DELAY));

            DeltaTime = (SDL_GetTicks() - PreviousFrameTime)/1000;

            if (event.type == SDL_QUIT) {
                quit = true;
                break;
            } else if (event.type == SDL_KEYDOWN) {
                int pacmanY = Pacman.getPacmanPos(UpdatedState).first;
                int pacmanX = Pacman.getPacmanPos(UpdatedState).second;

                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        if (pacmanY > 0 && UpdatedState[pacmanY - 1][pacmanX] != '#' && UpdatedState[pacmanY - 1][pacmanX] != '=' && UpdatedState[pacmanY - 1][pacmanX] != '0' && UpdatedState[pacmanY - 1][pacmanX] != '1' && UpdatedState[pacmanY - 1][pacmanX] != '2' && UpdatedState[pacmanY - 1][pacmanX] != '3') {
                            UpdatedState[pacmanY][pacmanX] = ' ';
                            --pacmanY;
                            UpdatedState[pacmanY][pacmanX] = '9';
                        }
                        Pacman.Direction = Pacman.FIRST_NORTH;
                        break;
                    case SDLK_DOWN:
                        if (pacmanY < UpdatedState.size() - 1 && UpdatedState[pacmanY + 1][pacmanX] != '#' && UpdatedState[pacmanY + 1][pacmanX] != '=' && UpdatedState[pacmanY + 1][pacmanX] != '0' && UpdatedState[pacmanY + 1][pacmanX] != '1' && UpdatedState[pacmanY + 1][pacmanX] != '2' && UpdatedState[pacmanY + 1][pacmanX] != '3') {
                            UpdatedState[pacmanY][pacmanX] = ' ';
                            ++pacmanY;
                            UpdatedState[pacmanY][pacmanX] = '9';
                        }
                        Pacman.Direction = Pacman.FIRST_SOUTH;
                        break;
                    case SDLK_LEFT:
                        if (pacmanX > 0 && UpdatedState[pacmanY][pacmanX - 1] != '#' && UpdatedState[pacmanY][pacmanX - 1] != '=' && UpdatedState[pacmanY][pacmanX - 1] != '0' && UpdatedState[pacmanY][pacmanX - 1] != '1' && UpdatedState[pacmanY][pacmanX - 1] != '2' && UpdatedState[pacmanY][pacmanX - 1] != '3') {
                            UpdatedState[pacmanY][pacmanX] = ' ';
                            --pacmanX;
                            UpdatedState[pacmanY][pacmanX] = '9';
                        }
                        Pacman.Direction = Pacman.FIRST_WEST;
                        break;
                    case SDLK_RIGHT:
                        if (pacmanX < UpdatedState[pacmanY].size() - 1 && UpdatedState[pacmanY][pacmanX + 1] != '#' && UpdatedState[pacmanY][pacmanX + 1] != '=' && UpdatedState[pacmanY][pacmanX + 1] != '0' && UpdatedState[pacmanY][pacmanX + 1] != '1' && UpdatedState[pacmanY][pacmanX + 1] != '2' && UpdatedState[pacmanY][pacmanX + 1] != '3') {
                            UpdatedState[pacmanY][pacmanX] = ' ';
                            ++pacmanX;
                            UpdatedState[pacmanY][pacmanX] = '9';
                        }
                        Pacman.Direction = Pacman.FIRST_EAST;
                        break;
                    default:
                        nextSprite = HandlePacmanMovement(Pacman, UpdatedState, nextSprite, DeltaTime);
                        break;
                }
            }
            delay();
            Uint32 CurrentTime = SDL_GetTicks();
            DeltaTime = (CurrentTime - PreviousFrameTime) / 1000.0f;
            PreviousFrameTime = CurrentTime;

           
        }
            if (CheckWall(UpdatedState, Pacman))
                nextSprite = HandlePacmanMovement(Pacman, UpdatedState, nextSprite, DeltaTime);

            SDL_RenderClear(MainRenderer);
            DrawMap(MainRenderer, UpdatedState, Pacman, LoadMaps, nextSprite);
            SDL_SetRenderDrawColor(MainRenderer, 0, 0, 0, 255);
            SDL_RenderPresent(MainRenderer);

    }

    return 0;
}

void Init() {
    SDL_Init(SDL_INIT_EVERYTHING);
    GameWindow = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    MainRenderer = SDL_CreateRenderer(GameWindow, -1, SDL_RENDERER_ACCELERATED);

    std::string const name = "C:\\Users\\zulul\\Documents\\pacman\\pacman\\files\\resources\\sprites\\icon.png";
    SDL_Surface* iconSurface = IMG_Load(name.c_str());
    if (iconSurface == nullptr) {
        printf("Failed to load window icon image! SDL_ERROR: %s\n", SDL_GetError());
        return;
    }
    SDL_SetWindowIcon(GameWindow, iconSurface);
    SDL_FreeSurface(iconSurface);

}

void DrawMap(SDL_Renderer *renderer, Map One, pacman Pacman, Window LoadMap,int SpriteNum) {
    SDL_Rect Wall = {0, 0, 0, 0};
    SDL_Texture* PacmanTextures = nullptr;
    SDL_Rect PacmanRect = {0, 0, 0, 0};

    for (int y = 0; y < LIMIT; y++) {
        for (int x = 0; x < LIMIT; x++) {
            Wall = {(x + 7) * CELL_SIZE, (y + 7) * CELL_SIZE, CELL_SIZE, CELL_SIZE};

            switch (One[y][x]) {
                case '#':
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                    SDL_RenderFillRect(renderer, &Wall);
                    break;
                case '.':
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderDrawPoint(renderer, Wall.x + CELL_SIZE / 2, Wall.y + CELL_SIZE / 2);
                    break;
                case '9':
                
                        switch (Pacman.Direction) {
                            case Pacman.FIRST_SOUTH:
                                Wall.w = 13;
                                Wall.h = 12;
                                PacmanTextures = Pacman.LoadSprites(renderer,Wall.w,Wall.h,Pacman.Loc[Pacman.FIRST_SOUTH]);
                            case Pacman.SECOND_SOUTH:
                                Wall.w = 13;
                                Wall.h = 9;
                                PacmanTextures = Pacman.LoadSprites(renderer,Wall.w,Wall.h,Pacman.Loc[Pacman.SECOND_SOUTH]);
                                break;
                            
                            case Pacman.FIRST_EAST:
                                Wall.w = 12;
                                Wall.h = 13;
                                PacmanTextures = Pacman.LoadSprites(renderer,Wall.w,Wall.h,Pacman.Loc[Pacman.FIRST_WEST]);
                            case Pacman.SECOND_EAST:
                                Wall.w = 9;
                                Wall.h = 13;
                                PacmanTextures = Pacman.LoadSprites(renderer,Wall.w,Wall.h,Pacman.Loc[Pacman.SECOND_WEST]);
                                break;
                            case Pacman.FIRST_NORTH:
                                Wall.w = 13;
                                Wall.h = 12;
                                PacmanTextures = Pacman.LoadSprites(renderer,Wall.w,Wall.h,Pacman.Loc[Pacman.FIRST_NORTH]);
                            case Pacman.SECOND_NORTH:
                                Wall.w = 13;
                                Wall.h = 9;
                                PacmanTextures = Pacman.LoadSprites(renderer,Wall.w,Wall.h,Pacman.Loc[Pacman.SECOND_NORTH]);
                                break;
                            case Pacman.FIRST_WEST:
                                Wall.w = 12;
                                Wall.h = 13;
                                PacmanTextures = Pacman.LoadSprites(renderer,Wall.w,Wall.h,Pacman.Loc[Pacman.FIRST_EAST]);
                                break;
                            case Pacman.SECOND_WEST:
                                Wall.w = 9;
                                Wall.h = 13;
                                PacmanTextures = Pacman.LoadSprites(renderer,Wall.w,Wall.h,Pacman.Loc[Pacman.SECOND_EAST]);
                                break;
                            default:
                                break;
                        }
                        PacmanRect = {Wall.x, Wall.y, CELL_SIZE-5,CELL_SIZE-5};
                        SDL_RenderCopy(renderer, PacmanTextures, nullptr, &PacmanRect);
                        SDL_DestroyTexture(PacmanTextures);

                    break;
                case 'o':
                    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
                    SDL_RenderDrawPoint(renderer, Wall.x + CELL_SIZE / 2, Wall.y + CELL_SIZE / 2);
                    LoadMap.DrawCircle(renderer, Wall.x + CELL_SIZE / 2, Wall.y + CELL_SIZE / 2, CELL_SIZE / 6);
                    break;
                case '=':
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderFillRect(renderer, &Wall);
                    break;
                default:
                    break;
            }
        }
    }
}


int HandlePacmanMovement(pacman& Pacman, Map& UpdatedState, int Index, float DeltaTime) {
    int pacmanY = Pacman.getPacmanPos(UpdatedState).first;
    int pacmanX = Pacman.getPacmanPos(UpdatedState).second;

    // Update Pacman's position based on direction and delta time
    switch (Pacman.Direction) {
        case Pacman.FIRST_SOUTH:
        case Pacman.SECOND_SOUTH:
            pacmanY += static_cast<int>(PacmanSpeed * DeltaTime);
            break;
        case Pacman.FIRST_EAST:
        case Pacman.SECOND_EAST:
            pacmanX += static_cast<int>(PacmanSpeed * DeltaTime);
            break;
        case Pacman.FIRST_NORTH:
        case Pacman.SECOND_NORTH:
            pacmanY -= static_cast<int>(PacmanSpeed * DeltaTime);
            break;
        case Pacman.FIRST_WEST:
        case Pacman.SECOND_WEST:
            pacmanX -= static_cast<int>(PacmanSpeed * DeltaTime);
            break;
        default:
            break;
    }

    // Update Pacman's position in the map
    UpdatedState[pacmanY][pacmanX] = '9';

    return 0;
}


/*case '0':
                
                if (!BlinkySprites.empty())
                {
                    SDL_Texture *spriteTexture = LoadSprite(Located[0], renderer, 0); // Assuming Blinky is at index 0
                    if (spriteTexture != nullptr)
                    {
                        SDL_RenderCopy(renderer, spriteTexture, nullptr, &Wall);
                        SDL_DestroyTexture(spriteTexture);
                    }
                }
                break;
            case '1':
                
                if (!InkySprites.empty())
                {
                    SDL_Texture *spriteTexture = LoadSprite(Located[1], renderer, 0); // Assuming Inky is at index 1
                    if (spriteTexture != nullptr)
                    {
                        SDL_RenderCopy(renderer, spriteTexture, nullptr, &Wall);
                        SDL_DestroyTexture(spriteTexture);
                    }
                }
                break;
            case '2':
                
                if (!PinkySprites.empty())
                {
                    SDL_Texture *spriteTexture = LoadSprite(Located[2], renderer, 0); // Assuming Pinky is at index 2
                    if (spriteTexture != nullptr)
                    {
                        SDL_RenderCopy(renderer, spriteTexture, nullptr, &Wall);
                        SDL_DestroyTexture(spriteTexture);
                    }
                }
                break;
            case '3':
                
                if (!ClydeSprites.empty())
                {
                    SDL_Texture *spriteTexture = LoadSprite(Located[3], renderer, 0); // Assuming Clyde is at index 3
                    if (spriteTexture != nullptr)
                    {
                        SDL_RenderCopy(renderer, spriteTexture, nullptr, &Wall);
                        SDL_DestroyTexture(spriteTexture);
                    }
                }
                break;*/



                
    /*DrawMap(MainRenderer, UpdatedState, Pacman, LoadMaps);
    SDL_RenderPresent(MainRenderer);

    Uint32 previousFrameTime = SDL_GetTicks();
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
                break;
            }
        }

        Uint32 elapsedTime = SDL_GetTicks() - previousFrameTime;
        if (elapsedTime < 1000 / 30) {
            SDL_Delay(1000 / 30 - elapsedTime);
        }
        previousFrameTime = SDL_GetTicks();

        int pacmanY = Pacman.getPacmanPos(UpdatedState).second;
        int pacmanX = Pacman.getPacmanPos(UpdatedState).first;

        
            switch (Pacman.Direction) {
                case Pacman.FIRST_SOUTH:
                case Pacman.SECOND_SOUTH:
                    if (pacmanY < UpdatedState.size() - 1 && UpdatedState[pacmanY + 1][pacmanX] != '#') {
                        UpdatedState[pacmanY][pacmanX] = ' ';
                        pacmanY++;
                        UpdatedState[pacmanY][pacmanX] = '9';
                    }
                    break;
                case Pacman.FIRST_EAST:
                case Pacman.SECOND_EAST:
                    if (pacmanX < UpdatedState[pacmanY].size() - 1 && UpdatedState[pacmanY][pacmanX + 1] != '#') {
                        UpdatedState[pacmanY][pacmanX] = ' ';
                        pacmanX++;
                        UpdatedState[pacmanY][pacmanX] = '9';
                    }
                    break;
                case Pacman.FIRST_NORTH:
                case Pacman.SECOND_NORTH:
                    if (pacmanY > 0 && UpdatedState[pacmanY - 1][pacmanX] != '#') {
                        UpdatedState[pacmanY][pacmanX] = ' ';
                        pacmanY--;
                        UpdatedState[pacmanY][pacmanX] = '9';
                    }
                    break;
                case Pacman.FIRST_WEST:
                case Pacman.SECOND_WEST:
                    if (pacmanX > 0 && UpdatedState[pacmanY][pacmanX - 1] != '#') {
                        UpdatedState[pacmanY][pacmanX] = ' ';
                        pacmanX--;
                        UpdatedState[pacmanY][pacmanX] = '9';
                    }
                    break;
                default:
                    break;
            }
        

        DrawMap(MainRenderer, UpdatedState, Pacman, LoadMaps);
    }
*/