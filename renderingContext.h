#ifndef RENDERINGCONTEXT_H_INCLUDED
#define RENDERINGCONTEXT_H_INCLUDED

#include <SDL2/SDL.h>
#include "point.h"
#include "specs.h"

class Tetromino;
class Playfield;

class RenderingContext {
    public:
        using Type = tetris::TetroType;

        RenderingContext();

        void render(const Playfield& playfield) const;
        void render(const Tetromino& tetromino) const;
        void eraseTetro(const Tetromino& tetromino) const;

        void updateScreen() const;

        ~RenderingContext();
    private:
        //state
        SDL_Window* window;
        SDL_Renderer* renderer;

        //methods;
        void initWindow();
        void initRenderer();

        void renderBlock(int x, int y, Type type) const;
};

#endif // RENDERINGCONTEXT_H_INCLUDED
