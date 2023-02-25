#include "Tile.hpp"

LTexture cross;
LTexture circle;

Tile::Tile(){
    occupiedPlaces = 0;
    totalPlaces = 9;
}

void Tile::drawChar(){
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            switch(piece[i][j]){
            case crossPiece:
                drawCross(i, j);
                break;
            case circlePiece:
                drawCircle(i, j);
                break;
            } 
        }
    }   
}

void Tile::place(int row, int col){
    if(occupiedPlaces < totalPlaces){
        if(occupiedPlaces % 2 == 0){
            piece[row][col] = crossPiece;
        }else{
            piece[row][col] = circlePiece;
        }
        occupiedPlaces++;
    }
}

void Tile::drawCross(int row, int col){
    int fieldSize = 160;

    cross.loadFromFile("C:/Users/irina/Desktop/Projects/TicTacToe/src/cross.png");
    cross.renderTextures(fieldSize * col, fieldSize * row);
}

void Tile::drawCircle(int row, int col){
    int fieldSize = 160;
    
    circle.loadFromFile("C:/Users/irina/Desktop/Projects/TicTacToe/src/circle.png");
    circle.renderTextures(fieldSize * col, fieldSize * row);
}

bool Tile::hasWinner() const{
    return (checkRows() || checkColumns() || checkDiagonals());
}

bool Tile::isFilled() const{
    return occupiedPlaces == 9;
}

void Tile::restart(){
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            piece[i][j] = emptyPiece;
        }
    }
    occupiedPlaces = 0;
    SDL_RenderClear(gRenderer);
}

bool Tile::checkRows() const{
    if(piece[0][0] == piece[0][1] && piece[0][1] == piece[0][2] && !isFieldEmpty(0,2)){
        return true;
    }else if(piece[1][0] == piece[1][1] && piece[1][1] == piece[1][2] && !isFieldEmpty(1,2)){
        return true;
    }else if(piece[2][0] == piece[2][1] && piece[2][1] == piece[2][2] && !isFieldEmpty(2,2)){
        return true;
    }
    return false;
}

bool Tile::checkColumns() const{
    if(piece[0][0] == piece[1][0] && piece[1][0] == piece[2][0] && !isFieldEmpty(2,0)){
        return true;
    }else if(piece[0][1] == piece[1][1] && piece[1][1] == piece[2][1] && !isFieldEmpty(2,1)){
        return true;
    }else if(piece[0][2] == piece[1][2] && piece[1][2] == piece[2][2] && !isFieldEmpty(2,2)){
        return true;
    }
    return false;
}

bool Tile::checkDiagonals() const{
    if(piece[0][0] == piece[1][1] && piece[1][1] == piece[2][2] && !isFieldEmpty(2,2)){
        return true;
    }else if(piece[0][2] == piece[1][1] && piece[1][1] == piece[2][0] && !isFieldEmpty(2,0)){
        return true;
    }
    return false;
}

bool Tile::isFieldEmpty(int row, int col) const{
    if(row>=0 && row<3 && col>=0 && col<3){
        return piece[row][col] == emptyPiece;
    }
    return false;
}

Tile::~Tile(){
    deleteChar();
}

void Tile::deleteChar(){
    cross.free();
    circle.free();
    occupiedPlaces = 0;
}