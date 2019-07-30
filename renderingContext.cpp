#include <stdexcept>
#include "renderingContext.h"
#include "tetromino.h"
#include "playfield.h"

#include <iostream>

using Type = tetris::TetroType;

RenderingContext::RenderingContext() : window{nullptr}, renderer{nullptr} {
    initWindow();
    initRenderer();
}

RenderingContext::~RenderingContext() {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;
}

void RenderingContext::initWindow() {
    int width = tetris::fieldWidth * tetris::blockWidth;
    int height = tetris::fieldHeight * tetris::blockHeight;
    window = SDL_CreateWindow("Tetris - Reloaded", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            width, height, SDL_WINDOW_SHOWN);

    if(!window) throw std::runtime_error(SDL_GetError());
}

void RenderingContext::initRenderer() {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!renderer) {
        SDL_DestroyWindow(window);
        window = nullptr;
        throw std::runtime_error(SDL_GetError());
    }
}

void RenderingContext::render(const Playfield& field) const {
    auto fieldState = field.getFieldState();
    for(int row = 0; row < tetris::fieldHeight; row++) {
        for(int col = 0; col < tetris::fieldWidth; col++) {
            renderBlock(col, row, fieldState[row][col]);
        }
    }
}

void RenderingContext::render(const Tetromino& tetro) const {
    for(Point center : tetro.getBody()) {
        int x = floor(center.x);
        int y = floor(center.y);
        renderBlock(x, y, tetro.getType());
    }
}

void RenderingContext::eraseTetro(const Tetromino& tetro) const {
    for(Point center : tetro.getBody()) {
        int x = floor(center.x);
        int y = floor(center.y);
        renderBlock(x, y, Type::E);
    }
}

void RenderingContext::renderBlock(int x, int y, Type type) const {
    SDL_Rect block{x * tetris::blockWidth, y * tetris::blockHeight, tetris::blockWidth, tetris::blockHeight};
    SDL_Color c = tetris::colors[type];
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderFillRect(renderer, &block);
}

void RenderingContext::updateScreen() const {
    SDL_RenderPresent(renderer);
}
