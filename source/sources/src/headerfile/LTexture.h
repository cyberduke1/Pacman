#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <SDL2/SDL.h>

class LTexture{

    public:
        LTexture();
        ~LTexture();

        bool loadFromFile( std::string path,SDL_Renderer* Render);

        
        void free();

        //Renders texture at given point
        void render( int x, int y, SDL_Rect* clip = NULL ,SDL_Renderer* Render);

        //Gets image dimensions
        int getWidth();
        int getHeight();

    private:
        
        SDL_Texture* mTexture;
        //Image dimensions
        int mWidth;
        int mHeight;

};
#endif