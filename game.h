#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <array>
#include "renderingContext.h"
#include "specs.h"
#include "point.h"

class Tetromino;
class Playfield;

class Game {
    public:
        using Type = tetris::TetroType;
        using Body = std::array<Point, 4>;

        Game(RenderingContext& renderingContext);
        ~Game();
        void startGame();

    private:
        //state
        const RenderingContext& renderingContext;
        Tetromino* tetro;
        Playfield* playfield;
        std::array<Type, 7> sequence{Type::I, Type::O, Type::T, Type::J, Type::L, Type::S, Type::Z};
        int seqIndex;

        //methods
        void initGameState();
        void startMainLoop();

        void shuffleSequence();
        void resetTetro();

        bool handleUserInput();
        void handleKeyPress(SDL_Event& e);

        bool isPossibleMove(const Body& projection) const;
        bool isOutOfBounds(const Body& projection) const;
        bool isColliding(const Body& projection) const;
};

#endif // GAME_H_INCLUDED
