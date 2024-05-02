#include "headerfile/Window.h"
#include "Window.h"


Window::Window() {
    Windows = nullptr;
    WindowSurface = nullptr;
    Limit = limit(WINDOW_HEIGHT);
    Renders = nullptr;
    
}

SDL_Window* Window::InitializeWindow() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize!\n SDL_ERROR :  %s", SDL_GetError());
        return nullptr;
    }

    SDL_Window* window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        printf("SDL could not create the window! \n SDL_ERROR : %s", SDL_GetError());
        return nullptr;
    }

    std::string const name = "C:\\Users\\zulul\\Documents\\pacman\\Pacman\\source\\resources\\sprites\\icon.png";
    SDL_Surface* iconSurface = IMG_Load(name.c_str());
    if (iconSurface == nullptr) {
        printf("Failed to load window icon image! SDL_ERROR: %s\n", SDL_GetError());
        return nullptr;
    }
    SDL_SetWindowIcon(window, iconSurface);
    SDL_FreeSurface(iconSurface);

    WindowSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(WindowSurface, nullptr, SDL_MapRGB(WindowSurface->format, 0, 0, 0));
    SDL_UpdateWindowSurface(window);

    return window;
}


void Window::WindowShown() {
    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;
        }
    }
}

int Window::limit(int window_height)
{
    int answer = window_height/21;
    return answer;
}

void Window::RenderBlinky(int x, int y, SDL_Renderer* Render,SDL_Window* window,int frameIndex)
{
    //C:\\Users\\zulul\\Documents\\pacman\\Pacman\\source\\resources\\sprites\\blinky.png
    std::string Location = "C:\\Users\\zulul\\Documents\\pacman\\Pacman\\source\\resources\\sprites\\blinky.png";
    
    int frameWidth = 17;
    int frameHeight = CELL_SIZE;

    
    


    int srcX = frameIndex * frameWidth;
    int srcY = 0;

    int destX = x;
    int destY = y;

    
    
}


void Window::RenderInky(int x, int y, SDL_Renderer* Render,SDL_Window* window,int frameIndex)
{
    //C:\\Users\\zulul\\Documents\\pacman\\Pacman\\source\\resources\\sprites\\inky.png
    std::string Location = "C:\\Users\\zulul\\Documents\\pacman\\Pacman\\source\\resources\\sprites\\inky.png";
    
    int frameWidth = 17;
    int frameHeight = CELL_SIZE;

    
    


    int srcX = frameIndex * frameWidth;
    int srcY = 0;

    int destX = x;
    int destY = y;

    
    
}

void Window::RenderClyde(int x, int y, SDL_Renderer* Render,SDL_Window* window,int frameIndex)
{
    //C:\\Users\\zulul\\Documents\\pacman\\Pacman\\source\\resources\\sprites\\clyde.png
    std::string Location = "C:\\Users\\zulul\\Documents\\pacman\\Pacman\\source\\resources\\sprites\\clyde.png";
    
    
    int frameWidth = 17;
    int frameHeight = CELL_SIZE;

    
    


    int srcX = frameIndex * frameWidth;
    int srcY = 0;

    int destX = x;
    int destY = y;

    
    
}

void Window::RenderPinky(int x, int y, SDL_Renderer* Render,SDL_Window* window,int frameIndex)
{
    //C:\\Users\\zulul\\Documents\\pacman\\Pacman\\source\\resources\\sprites\\Pinky.png
    std::string Location = "C:\\Users\\zulul\\Documents\\pacman\\Pacman\\source\\resources\\sprites\\Pinky.png";
    
    
    int frameWidth = 17;
    int frameHeight = CELL_SIZE;

    
    


    int srcX = frameIndex * frameWidth;
    int srcY = 0;

    int destX = x;
    int destY = y;

    
    
}

void Window::RenderPacman(int x, int y, SDL_Renderer* Render,SDL_Window* window,int frameIndex)
{
    //Pacman thingie
    std::string Location = "C:\\Users\\zulul\\Documents\\pacman\\Pacman\\source\\resources\\sprites\\pacman.png";
    
    
    int frameWidth = 17;
    int frameHeight = CELL_SIZE;

    
    


    int srcX = frameIndex * frameWidth;
    int srcY = 0;

    int destX = x;
    int destY = y;

    
    
}

SDL_Texture* Window::loadTexture(std::string Location, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(Location.c_str());
    if (loadedSurface == nullptr) {
        std::cout << "Unable to load image " << Location << "! SDL_image Error: " << IMG_GetError() << std::endl;
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr) {
            std::cout << "Unable to create texture from " << Location << "! SDL Error: " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

bool Window::RenderOnSurface(std::string Location, int x, int y, SDL_Renderer* renderer) {

    SDL_Texture* texture = loadTexture(Location, renderer);

    if (texture == nullptr) {
        return false; 
    }

    SDL_Rect srcRect; 
    srcRect.x = 0; 
    srcRect.y = 0; 
    srcRect.w = CELL_SIZE; 
    srcRect.h = CELL_SIZE; 

    SDL_Rect destRect; 
    destRect.x = x;
    destRect.y = y;
    destRect.w = CELL_SIZE;
    destRect.h = CELL_SIZE;

    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(texture);

    return true;
}


bool Window::loadSprite(std::string Location,int width,int height,SDL_Renderer* Render,SDL_Window* window) {
    
    bool Loaded = true;
    int imgFlags = IMG_INIT_PNG;

    if (!(IMG_Init(imgFlags) & imgFlags) && (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))) {
        printf("SDL_Image could not initialize!\n SDL_Image Error: %s", IMG_GetError());
        Loaded = false;
    } else {
        WindowSurface = SDL_GetWindowSurface(Windows);
        Loaded = RenderOnSurface(Location,width,height,Render,window);
    }

    return Loaded;
}


void Window::InitialLoad(SDL_Renderer *renderer)
{
    for(int i = 0 ; i < Located.size()-1;i++){
        switch (i)
        {
        case 0:
            BlinkySprites.push_back(loadTexture(Located[i],renderer));
            break;
        case 1:
            InkySprites.push_back(loadTexture(Located[i],renderer));
            break;
        case 2:
            PinkySprites.push_back(loadTexture(Located[i],renderer));
            break;
        case 3:
            ClydeSprites.push_back(loadTexture(Located[i],renderer));
            break;
        case 4:
            PacmanSprites.push_back(loadTexture(Located[i],renderer));
            break;

        default:
            break;
        }
    }
}

bool Window::renderFrameOnSurface(std::string Location, int srcX, int srcY, int srcWidth, int srcHeight, int destX, int destY, SDL_Renderer* renderer,SDL_Texture* texture) {

    
    if (texture == nullptr) {
        return false;
    }

    
    SDL_Rect srcRect;
    srcRect.x = srcX;
    srcRect.y = srcY;
    srcRect.w = srcWidth;
    srcRect.h = srcHeight;

    
    SDL_Rect destRect; 
    destRect.x = destX;
    destRect.y = destY;
    destRect.w = srcWidth;
    destRect.h = srcHeight;

    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(texture);

    return true;
}

void Window::getRender(SDL_Renderer* render){
    Renders = render;
}

bool Window::DrawMap(SDL_Renderer* renderer, Map One,SDL_Window* window) {
    
    SDL_Rect Wall = {0, 0, 0, 0};
    bool FullyRan = false;
    int radius, centerX, centerY, rad, pointX, pointY;
    for (int y = 0; y < LIMIT; y++) {
        for (int x = 0; x < LIMIT; x++) {
            Wall = {(x + 13) * CELL_SIZE, (y+13) * CELL_SIZE, CELL_SIZE, CELL_SIZE};

            switch (One[y][x]) {
                case '#':
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                    SDL_RenderFillRect(renderer, &Wall);
                    break;
                case '.':
                    radius = CELL_SIZE / 8;
                    centerX = Wall.x + CELL_SIZE / 2;
                    centerY = Wall.y + CELL_SIZE / 2;

                    // Fill circle with gradient color
                    for (int r = 0; r <= radius; ++r) {
                        // Calculate color intensity based on distance from center
                        Uint8 intensity = 255 * (1.0 - (double)r / radius);

                        // Set color with calculated intensity
                        SDL_Color fill_color = {intensity, intensity, intensity, 255};

                        // Draw filled circle with current radius
                        drawFilledCircle(renderer, centerX, centerY, r);
                    }
                    break;
                case '0':
                    RenderBlinky(Wall.x,Wall.y,renderer,window,0);
                    break;
                case '1':
                    RenderInky(Wall.x,Wall.y,renderer,window,1);
                    break;
                case '2':
                    RenderPinky(Wall.x,Wall.y,renderer,window,2);
                    break;
                case '3':
                    RenderClyde(Wall.x,Wall.y,renderer,window,3);
                    break;
                case '9':
                    RenderPacman(Wall.x,Wall.y,renderer,window,4);
                    break;
                case 'o':
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                    SDL_RenderDrawPoint(renderer, (x + 13) * CELL_SIZE, (y+13) * CELL_SIZE);
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
    FullyRan = true;
    
    return FullyRan;
}


void Window::drawFilledCircle(SDL_Renderer * renderer, int centerX, int centerY, int radius)
{
    SDL_SetRenderDrawColor(renderer,255, 255, 255, 255);
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            }
        }
    }
}


Window::~Window() {
    SDL_DestroyWindow(Windows);
    SDL_Quit();
}
