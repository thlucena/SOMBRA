#include "canvas.h"

Pixel::Pixel(int x_coord, int y_coord) {
    x = x_coord;
    y = y_coord;
}

Pixel::Pixel(int x_coord, int y_coord, uchar red, uchar green, uchar blue) {
    x = x_coord;
    y = y_coord;
    color.setValues(red, green, blue);
}

int Pixel::getX() const{
    return x;
}

int Pixel::getY() const{
    return y;
}

Color Pixel::getColor() {
    return color;
}

void Pixel::setColor(uchar red, uchar green, uchar blue) {
    color.setValues(red, green, blue);
}

bool Pixel::operator == (const Pixel& rhs) {
    return this->x == rhs.getX() && this->y == rhs.getY();
}
bool Pixel::operator != (const Pixel& rhs) {
    return !(*this == rhs);
}