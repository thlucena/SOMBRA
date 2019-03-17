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

Pixel::Pixel(int x_coord, int y_coord, Color c) {
    x = x_coord;
    y = y_coord;
    color = c;
}

int Pixel::getX() const{
    return x;
}

int Pixel::getY() const{
    return y;
}

Color Pixel::getColor() const{
    return color;
}

void Pixel::setColor(uchar red, uchar green, uchar blue) {
    color.setValues(red, green, blue);
}

void Pixel::setColor(Color new_color) {
    color.setValues(new_color.red(), new_color.green(), new_color.blue());
}

Pixel Pixel::neighborN() {
    return Pixel(x, y-1, color);
}

Pixel Pixel::neighborS() {
    return Pixel(x, y+1, color);
}

Pixel Pixel::neighborE() {
    return Pixel(x+1, y, color);
}

Pixel Pixel::neighborW() {
    return Pixel(x-1, y, color);
}

bool Pixel::operator == (const Pixel& rhs) {
    return this->x == rhs.getX() && this->y == rhs.getY();
}
bool Pixel::operator != (const Pixel& rhs) {
    return !(*this == rhs);
}