#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

struct Point {
    double x;
    double y;

    Point() {}

    Point(double x, double y) : x{x}, y{y} {}
};

#endif // POINT_H_INCLUDED
