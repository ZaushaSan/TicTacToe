#ifndef TILE_HPP
#define TILE_HPP

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include "App.hpp"
#include "LTexture.hpp"

class Tile{
    public:
        enum pieces{
            emptyPiece,
            crossPiece,
            circlePiece
        };

        Tile();
        ~Tile();

        void drawCircle(int row, int col);
        void drawCross(int row, int col);
        void drawChar();
        void deleteChar();

        bool hasWinner() const;
        bool isFilled() const;
        bool isFieldEmpty(int row, int col) const;

        bool checkRows() const;
        bool checkColumns() const;
        bool checkDiagonals() const;

        void restart();
        void place(int row, int col);
    private:
        pieces piece[3][3];

        int occupiedPlaces;
        int totalPlaces;
};

#endif