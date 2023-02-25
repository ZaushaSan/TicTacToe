#ifndef APP_HPP
#define APP_HPP

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include "stdio.h"
#include "LTexture.hpp"
#include "Tile.hpp"
#include "globals.hpp"

class App{
    public:
        static const int SCREEN_WIDTH = 480;
        static const int SCREEN_HEIGHT = 480;

        ~App();

        bool init();

        void loop();
        void close();
        void render();
        void update(SDL_Event *e);
        void checkWin(SDL_Event *e);
};

#endif