#ifndef LTEXTURE_HPP
#define LTEXTURE_HPP

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include "globals.hpp"
#include <string>

class LTexture{
    public:
        LTexture();
        ~LTexture();

        bool loadFromFile(std::string path);
        #if defined(SDL_TTF_MAJOR_VERSION)
        bool loadFromRenderedText(std::string textTexture, SDL_Color textColor);
        #endif

        void free();

        int getWidth();
        int getHeight();

        void renderTextures(int x, int y);

        SDL_Texture *mTexture;
        int mWidth;
        int mHeight;
};

#endif