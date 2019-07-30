#include "tetromino.h"

using Body = std::array<Point, 4>;
using Type = tetris::TetroType;

Tetromino::Tetromino() {
    resetTo(Type::E);
}

const Body& Tetromino::getBody() const {
    return body;
}

void Tetromino::moveLeft() {
    body = moveLeftProjection();
    --pivot.x;
}

void Tetromino::moveRight() {
    body = moveRightProjection();
    ++pivot.x;
}

void Tetromino::moveDown() {
    body = moveDownProjection();
    ++pivot.y;
}

void Tetromino::rotate() {
    body = rotateProjection();
}

Body Tetromino::moveLeftProjection() const {
    Body projection = body;
    for(Point& blockCenter : projection) {
        --blockCenter.x;
    }
    return projection;
}

Body Tetromino::moveRightProjection() const {
    Body projection = body;
    for(Point& blockCenter : projection) {
        ++blockCenter.x;
    }
    return projection;
}

Body Tetromino::moveDownProjection() const {
    Body projection = body;
    for(Point& blockCenter : projection) {
        ++blockCenter.y;
    }
    return projection;
}

Body Tetromino::rotateProjection() const {
    Body projection = body;
    for(Point& blockCenter : projection) {
        blockCenter = rotateClockwise(blockCenter);
    }
    return projection;
}

Point Tetromino::rotateClockwise(const Point& p) const {
    Point relativePos{p.x - pivot.x, p.y - pivot.y};
    Point rotatedPos{-relativePos.y, relativePos.x};
    return Point{rotatedPos.x + pivot.x, rotatedPos.y + pivot.y};
}

Type Tetromino::getType() const {
    return type;
}

void Tetromino::resetTo(Type type) {
    this->type = type;
    pivot = tetris::initPivots[type];
    body = tetris::initBodies[type];
}
