#include <SDL2/SDL.h>
#include <iostream>
#include "renderingContext.h"
#include "game.h"

int main() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Could not initialize video subsystem: " << SDL_GetError();
        return -1;
    }
    RenderingContext renderingContext = RenderingContext();
    Game game(renderingContext);
    game.startGame();
    SDL_Quit();
    return 0;
}
