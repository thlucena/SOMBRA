#ifndef _CANVAS_
#define _CANVAS_
#include <memory>

typedef unsigned char uchar;
enum Color { R = 0, G, B };

class Point {
    private:
        int x, y;
        /// Default color is black
        uchar color[3] {0};
    public:
        Point(int, int);
        Point(int, int, uchar, uchar, uchar);
        uchar* getColor();
        int getX();
        int getY();
};

class Canvas {
    private:
        int width, height;
        std::shared_ptr<uchar[]> pixels;
    public:
        Canvas();
        Canvas(int, int);
        void printToFile();
        void drawPoint(Point);
};

#endif