#include "canvas.h"

int main(int argc, char** argv) {
    Canvas c = Canvas(300, 300);
    // Pixel p1 = Pixel(0, 0, 255, 0, 0);
    // Pixel p2 = Pixel(0, 1, 0, 255, 0);
    // Pixel p3 = Pixel(0, 2, 0, 0, 255);
    // Pixel p4 = Pixel(1, 0, 255, 255, 0);
    // Pixel p5 = Pixel(1, 1, 255, 255, 255);
    // Pixel p6 = Pixel(1, 2, 0, 0, 0);
    // c.drawPixel(p1);
    // c.drawPixel(p2);
    // c.drawPixel(p3);
    // c.drawPixel(p4);
    // c.drawPixel(p5);
    // c.drawPixel(p6);
    c.drawLineBresenham(Pixel(100, 150), Pixel(200, 50), Color(255, 0, 0));
    c.drawLineBresenham(Pixel(100, 50), Pixel(200, 150), Color(0, 255, 0));
    c.printToFile();
    return 0;
}