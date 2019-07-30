#ifndef TETROMINO_H_INCLUDED
#define TETROMINO_H_INCLUDED

#include <array>
#include "point.h"
#include "specs.h"

class Tetromino {
    public:
        using Body = std::array<Point, 4>;
        using Type = tetris::TetroType;

        Tetromino();

        Type getType() const;
        const Body& getBody() const;

        void resetTo(Type type);

        void moveLeft();
        void moveRight();
        void moveDown();

        Body moveLeftProjection() const;
        Body moveRightProjection() const;
        Body moveDownProjection() const;

        void rotate();
        Body rotateProjection() const;
    private:
        //state
        Type type;
        Point pivot;
        Body body;

        //methods
        Point rotateClockwise(const Point& p) const;
};


#endif // TETROMINO_H_INCLUDED
