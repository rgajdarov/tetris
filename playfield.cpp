#include "playfield.h"
#include "tetromino.h"

#include <iostream>

using Type = tetris::TetroType;
using Row = std::vector<Type>;
using Field = std::vector<Row>;

Playfield::Playfield() :
                        ceiling{tetris::fieldHeight},
                        fieldState(tetris::fieldHeight, Row(tetris::fieldWidth, Type::E))
{
}

Type Playfield::getBlockType(const Point& p) const {
    int x = floor(p.x);
    int y = floor(p.y);
    return fieldState[y][x];
}

const Field& Playfield::getFieldState() const {
    return fieldState;
}

void Playfield::lockTetro(const Tetromino& tetro) {
    addTetromino(tetro);
    removeFilledLines(tetro);
}

void Playfield::addTetromino(const Tetromino& tetro) {
    for(const Point& center : tetro.getBody()) {
        int x = floor(center.x);
        int y = floor(center.y);
        fieldState[y][x] = tetro.getType();
        ceiling = ceiling > y ? y : ceiling;
    }
}

void Playfield::removeFilledLines(const Tetromino& tetro) {
    int high = tetris::fieldHeight, low = 0;
    for(const Point& p : tetro.getBody()) {
        high = p.y < high ? p.y : high;
        low = p.y > low ? p.y : low;
    }
    for(; high <= low; high++) {
        if(isFilled(fieldState[high])) clearLine(high);
    }
}

bool Playfield::isFilled(const Row& row) const {
    for(const Type& t : row) {
        if(t == Type::E) return false;
    }
    return true;
}

void Playfield::clearLine(int row) {
    for(; row > ceiling; row--) {
        fieldState[row] = fieldState[row - 1];
    }
    setEmpty(fieldState[ceiling]);
    ++ceiling;
}

void Playfield::setEmpty(Row& row) {
    for(Type& t : row) {
        t = Type::E;
    }
}

void Playfield::clearPlayfield() {
    for(Row& row : fieldState) {
        setEmpty(row);
    }
}
