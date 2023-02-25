#include "LTexture.hpp"

LTexture::LTexture(){
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture(){
    free();
}

bool LTexture::loadFromFile(std::string path){
    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;
        
    SDL_FreeSurface(loadedSurface);

    mTexture = newTexture;
    return mTexture;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText(std::string textTexture, SDL_Color textColor){
    free();

    SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, textTexture.c_str(), textColor);

    mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

    mWidth = textSurface->w;
    mHeight = textSurface->h;
        
    SDL_FreeSurface(textSurface);

    return mTexture != NULL;
}
#endif

void LTexture::renderTextures(int x, int y){
    SDL_Rect quad = {x, y, mWidth, mHeight};

	SDL_RenderCopy(gRenderer, mTexture, NULL, &quad);
}

void LTexture::free(){
    if(mTexture != NULL){
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;  
    }
}

int LTexture::getWidth(){
    return mWidth;
}

int LTexture::getHeight(){
    return mHeight;
}