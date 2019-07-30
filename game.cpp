#include <algorithm>
#include <random>
#include <chrono>

#include "game.h"
#include "tetromino.h"
#include "playfield.h"

using Type = tetris::TetroType;
using Body = std::array<Point, 4>;

Game::Game(RenderingContext& renderingContext) : renderingContext{renderingContext} {
    tetro = new Tetromino();
    playfield = new Playfield();
    seqIndex = 0;
}

Game::~Game() {
    delete tetro;
    delete playfield;
}

void Game::startGame() {
    initGameState();
    startMainLoop();
}

void Game::initGameState() {
    tetro->resetTo(Type::E);
    playfield->clearPlayfield();
    shuffleSequence();
    seqIndex = 0;
}

void Game::startMainLoop() {
    tetro->resetTo(sequence[seqIndex]);
    while(!isColliding(tetro->getBody())) {
        renderingContext.render(*playfield);
        renderingContext.render(*tetro);
        renderingContext.updateScreen();

        Uint32 moveDownTimer = SDL_GetTicks();
        while(true) {
            Uint32 currentTime = SDL_GetTicks();
            if(currentTime - moveDownTimer > 300) {
                if(!isPossibleMove(tetro->moveDownProjection())) break;
                renderingContext.eraseTetro(*tetro);
                tetro->moveDown();
                renderingContext.render(*tetro);
                renderingContext.updateScreen();
                moveDownTimer = currentTime;
            }
            if(!handleUserInput()) return;
        }
        SDL_FlushEvent(SDL_KEYDOWN);
        playfield->lockTetro(*tetro);
        resetTetro();
    }
}

void Game::shuffleSequence() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(sequence.begin(), sequence.end(), std::default_random_engine(seed));
}

void Game::resetTetro() {
    ++seqIndex;
    if(seqIndex >= 7) {
        seqIndex = 0;
        shuffleSequence();
    }
    tetro->resetTo(sequence[seqIndex]);
}

bool Game::handleUserInput() {
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0) {
        if(e.type == SDL_QUIT) return false;
        if(e.type == SDL_KEYDOWN) handleKeyPress(e);
    }

    return true;
}

void Game::handleKeyPress(SDL_Event& e) {
    if(e.key.keysym.sym == SDLK_UP) {
        if(!isPossibleMove(tetro->rotateProjection())) return;
        renderingContext.eraseTetro(*tetro);
        tetro->rotate();
    } else if(e.key.keysym.sym == SDLK_DOWN) {
        if(!isPossibleMove(tetro->moveDownProjection())) return;
        renderingContext.eraseTetro(*tetro);
        tetro->moveDown();
    } else if(e.key.keysym.sym == SDLK_LEFT) {
        if(!isPossibleMove(tetro->moveLeftProjection())) return;
        renderingContext.eraseTetro(*tetro);
        tetro->moveLeft();
    } else if(e.key.keysym.sym == SDLK_RIGHT) {
        if(!isPossibleMove(tetro->moveRightProjection())) return;
        renderingContext.eraseTetro(*tetro);
        tetro->moveRight();
    }
    renderingContext.render(*tetro);
    renderingContext.updateScreen();
}

bool Game::isPossibleMove(const Body& projection) const {
    return !isOutOfBounds(projection) && !isColliding(projection);
}

bool Game::isOutOfBounds(const Body& projection) const {
    for(auto& center : projection) {
        int x = floor(center.x);
        int y = floor(center.y);
        if(x < 0 || x >= tetris::fieldWidth) return true;
        if(y >= tetris::fieldHeight) return true;
    }
    return false;
}

bool Game::isColliding(const Body& projection) const {
    for(auto& center : projection) {
        if(playfield->getBlockType(center) != Type::E) return true;
    }
    return false;
}
