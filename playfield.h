#ifndef PLAYFIELD_H_INCLUDED
#define PLAYFIELD_H_INCLUDED

#include <vector>
#include "specs.h"
#include "point.h"

class Tetromino;

class Playfield {
    public:
        using Type = tetris::TetroType;
        using Row = std::vector<Type>;
        using Field = std::vector<Row>;

        Playfield();

        Type getBlockType(const Point& p) const;
        const Field& getFieldState() const;

        void lockTetro(const Tetromino& tetro);
        void clearPlayfield();
    private:
        //state
        int ceiling;
        Field fieldState;

        //methods
        void addTetromino(const Tetromino& tetro);
        void removeFilledLines(const Tetromino& tetro);
        bool isFilled(const Row& row) const;
        void clearLine(int row);
        void setEmpty(Row& row);
};

#endif // PLAYState_H_INCLUDED
