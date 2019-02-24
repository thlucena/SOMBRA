#include "canvas.h"

int main(int argc, char** argv) {
    Canvas c = Canvas(300, 200);
    Point p1 = Point(0, 0, 255, 0, 0);
    Point p2 = Point(0, 1, 0, 255, 0);
    Point p3 = Point(0, 2, 0, 0, 255);
    Point p4 = Point(1, 0, 255, 255, 0);
    Point p5 = Point(1, 1, 255, 255, 255);
    Point p6 = Point(1, 2, 0, 0, 0);
    c.drawPoint(p1);
    c.drawPoint(p2);
    c.drawPoint(p3);
    c.drawPoint(p4);
    c.drawPoint(p5);
    c.drawPoint(p6);
    c.printToFile();
    return 0;
}