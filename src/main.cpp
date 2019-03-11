#include "canvas.h"

int main(int argc, char** argv) {
    Canvas c = Canvas(300, 300);

    c.drawLineBresenham(Pixel(150, 150), Pixel(180, 150), Color(0, 255, 255));
    c.drawLineBresenham(Pixel(150, 150), Pixel(120, 150), Color(255, 0, 255));
    c.drawLineBresenham(Pixel(150, 150), Pixel(150, 180), Color(100, 100, 100));
    c.drawLineBresenham(Pixel(150, 150), Pixel(150, 120), Color(0, 0, 0));

    c.drawLineBresenham(Pixel(150, 150), Pixel(180, 120), Color(255, 0, 0));
    c.drawLineBresenham(Pixel(150, 150), Pixel(180, 180), Color(0, 255, 0));
    c.drawLineBresenham(Pixel(150, 150), Pixel(120, 120), Color(255, 255, 0));
    c.drawLineBresenham(Pixel(150, 150), Pixel(120, 180), Color(0, 0, 255));

    c.drawLineBresenham(Pixel(150, 150), Pixel(170, 110), Color(255, 0, 0));
    c.drawLineBresenham(Pixel(150, 150), Pixel(190, 170), Color(0, 255, 0));
    c.drawLineBresenham(Pixel(150, 150), Pixel(110, 130), Color(255, 255, 0));
    c.drawLineBresenham(Pixel(150, 150), Pixel(130, 190), Color(0, 0, 255));
    
    c.printToFile();
    
    return 0;
}