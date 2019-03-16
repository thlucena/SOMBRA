#ifndef _CANVAS_
#define _CANVAS_
#include <memory>
#include <vector>

typedef unsigned char uchar;
enum RGB { R = 0, G, B };

class Color {
    private:
        uchar values[3] {0}; // default color 0
    public:
        Color() {}
        Color(uchar r, uchar g, uchar b) {
            values[R] = r;
            values[G] = g;
            values[B] = b;
        }
        uchar red() { return values[R]; }
        uchar green() { return values[G]; }
        uchar blue() { return values[B]; }
        uchar* getValues() {
            return values;
        }
        void setValues(uchar r, uchar g, uchar b) {
            values[R] = r;
            values[G] = g;
            values[B] = b;
        }
};

class Pixel {
    private:
        int x, y;
        Color color = Color();
    public:
        Pixel(int, int);
        Pixel(int, int, uchar, uchar, uchar);
        int getX() const;
        int getY() const;
        Color getColor();
        void setColor(uchar, uchar, uchar);
        bool operator == (const Pixel&);
        bool operator != (const Pixel&);
};

class Canvas {
    private:
        int width, height;
        std::shared_ptr<uchar[]> pixels;
        bool isValidCoordinate(Pixel);
        bool isValidCoordinate(int, int);
        int calcAngle(int, int, int, int);
    public:
        Canvas();
        Canvas(int, int);
        void printToFile();
        void drawPixel(Pixel);
        void drawPixel(int, int, Color);
        void drawLineBresenham(Pixel, Pixel, Color);
        void drawCircle(Pixel, int, Color);
        void drawPolyline(std::vector<Pixel>&, Color);
        void drawPolygon(std::vector<Pixel>&, Color);
        void drawArc(Pixel, Pixel, int, Color);
};

#endif