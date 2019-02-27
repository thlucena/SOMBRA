#include "canvas.h"

Point::Point(int x_coord, int y_coord) {
    x = x_coord;
    y = y_coord;
}

Point::Point(int x_coord, int y_coord, uchar red, uchar green, uchar blue) {
    x = x_coord;
    y = y_coord;
    color.setValues(red, green, blue);
}

int Point::getX() {
    return x;
}

int Point::getY() {
    return y;
}

Color Point::getColor() {
    return color;
}

void Point::setColor(uchar red, uchar green, uchar blue) {
    color.setValues(red, green, blue);
}