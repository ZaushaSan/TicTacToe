#include "App.hpp"

Tile board;

LTexture grid;

LTexture win;

LTexture someoneWins;
LTexture draw;

App::~App(){
    close();
}

bool App::init(){
    bool success = true;

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        success = false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    gWindow = SDL_CreateWindow("TicTacToe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)){
        printf("404 %s\t", IMG_GetError());
        success = false;
    }
    if(TTF_Init() == -1){
        printf("404 %s\t", TTF_GetError());
        success = false;
    }
    grid.loadFromFile("src/grid.png");
    win.loadFromFile("src/win.png");

    SDL_Color textColor = {255, 255, 255};
    gFont = TTF_OpenFont("src/IpanemaSecco-463W.ttf", 60);
    draw.loadFromRenderedText("DRAW", textColor);
    someoneWins.loadFromRenderedText("WIN", textColor);
    return success;
}

void App::loop(){
    bool quit = false;
    SDL_Event e;

    while(!quit){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                quit = true;
            }
            update(&e);
        }
        render();
        checkWin(&e);
    }
    close();
}

void App::render(){
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    grid.renderTextures((SCREEN_WIDTH - grid.getWidth()) / 2, 0);
    board.drawChar();

    SDL_RenderPresent(gRenderer);
}
void App::update(SDL_Event *e){
    if(e->type == SDL_MOUSEBUTTONDOWN){
        int x, y;
        SDL_GetMouseState(&x, &y);

        int row = y / 160;
        int col = x / 160;

        if(board.isFieldEmpty(row, col)){
            board.place(row, col);
        }
    }
}

void App::checkWin(SDL_Event *e){
    if(board.hasWinner()){
        win.renderTextures((SCREEN_WIDTH - win.getWidth()) / 2, (SCREEN_HEIGHT - win.getHeight()) / 2); //rectangle texture
        someoneWins.renderTextures((SCREEN_WIDTH - someoneWins.getWidth()) / 2, (SCREEN_HEIGHT - someoneWins.getHeight()) / 2); //text

        SDL_RenderPresent(gRenderer);
        SDL_Delay(5000);

        board.restart();
    }

    if(board.isFilled()){
        win.renderTextures((SCREEN_WIDTH - win.getWidth()) / 2, (SCREEN_HEIGHT - win.getHeight()) / 2);
        draw.renderTextures((SCREEN_WIDTH - draw.getWidth()) / 2, (SCREEN_HEIGHT - draw.getHeight()) / 2);
        
        SDL_RenderPresent(gRenderer);
        SDL_Delay(5000);

        board.restart();
    }
}

void App::close(){
    grid.free();
    win.free();
    draw.free();
    someoneWins.free();

    board.deleteChar();

    TTF_CloseFont(gFont);
    gFont = NULL;

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
