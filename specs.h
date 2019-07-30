#ifndef SPECS_H_INCLUDED
#define SPECS_H_INCLUDED

#include <SDL2/SDL.h>
#include <array>
#include "point.h"

namespace tetris{
    enum TetroType{I, O, T, J, L, S, Z, E};

    const int fieldHeight = 20;
    const int fieldWidth = 10;

    const int blockHeight = 32;
    const int blockWidth = 32;

    const SDL_Color background{96, 125, 139, 255};

    const std::array<SDL_Color, 8> colors = {{{3, 168, 244, 255}, {255, 234, 0, 255},
                                         {141, 36, 170, 255}, {13, 72, 161, 255},
                                         {255, 153, 0, 255}, {99, 221, 23, 255},
                                         {255, 0, 0, 255}, background}};

    const std::array<Point, 8> initPivots = {{{4, 2}, {4, 1},
                                            {4.5, 1.5}, {4.5, 1.5},
                                            {4.5, 1.5}, {4.5, 1.5},
                                            {4.5, 1.5}, {0, 0}}};

    const std::array<std::array<Point, 4>, 8> initBodies = {{{{{2.5, 1.5}, {3.5, 1.5}, {4.5, 1.5}, {5.5, 1.5}}},
                                                {{{3.5, 0.5}, {4.5, 0.5}, {3.5, 1.5}, {4.5, 1.5}}},
                                                {{{3.5, 1.5}, {4.5, 1.5}, {4.5, 0.5}, {5.5, 1.5}}},
                                                {{{3.5, 0.5}, {3.5, 1.5}, {4.5, 1.5}, {5.5, 1.5}}},
                                                {{{3.5, 1.5}, {4.5, 1.5}, {5.5, 1.5}, {5.5, 0.5}}},
                                                {{{3.5, 1.5}, {4.5, 1.5}, {4.5, 0.5}, {5.5, 0.5}}},
                                                {{{3.5, 0.5}, {4.5, 0.5}, {4.5, 1.5}, {5.5, 1.5}}},
                                                {{{0, 0}, {0, 0}, {0, 0}, {0, 0}}}}};

}

#endif // SPECS_H_INCLUDED
