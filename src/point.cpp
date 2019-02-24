#include "canvas.h"

Point::Point(int x_coord, int y_coord) {
    x = x_coord;
    y = y_coord;
}

Point::Point(int x_coord, int y_coord, uchar red, uchar green, uchar blue) {
    x = x_coord;
    y = y_coord;
    color[R] = red;
    color[G] = green;
    color[B] = blue;
}

uchar* Point::getColor() {
    return color;
}

int Point::getX() {
    return x;
}

int Point::getY() {
    return y;
}