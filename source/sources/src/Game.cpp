#include "mann.cpp"

#define FALSE 0
#define TRUE 1


Window MainWindow;
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Texture *Texture = nullptr;
int GameRunning = FALSE;



int initialize_window(void){

    if(SDL_Init(SDL_INIT_EVERYTHING )!= 0){

        std::cout<<SDL_GetError()<<"\n";
        return FALSE;
    }

    window = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MainWindow.WINDOW_WIDTH, MainWindow.WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(window == nullptr){
        std::cout<<SDL_GetError()<<"\n";
        return FALSE;
    }

    if(renderer == nullptr){
        std::cout<<SDL_GetError()<<"\n";
        return FALSE;
    }
    return TRUE;
}


void process_input(){
    SDL_Event e;
    bool quit = false;
    std::pair<int,int> pacmanPos = getPacmanPos(map);
    int pacmanX = pacmanPos.second; 
    int pacmanY = pacmanPos.first;


    SDL_PollEvent(&e);

    switch (e.type)
    {
    case SDL_QUIT:
        GameRunning = FALSE;
        break;
    case SDL_KEYDOWN:
        
        switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    GameRunning = FALSE;
                    break;
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
        break;
    default:
        break;
    }

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
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
}
void update(){
    
}
void render(){
    
}

void end_window(){

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}
int main(int agrv,char* argc[]){

    GameRunning = initialize_window();
    setup();

    while(GameRunning){
        process_input();
        update();
        render();
    }

    return 0;
}