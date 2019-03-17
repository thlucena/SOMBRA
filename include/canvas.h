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
        uchar red() const { return values[R]; }
        uchar green() const { return values[G]; }
        uchar blue() const { return values[B]; }
        uchar* getValues() {
            return values;
        }
        void setValues(uchar r, uchar g, uchar b) {
            values[R] = r;
            values[G] = g;
            values[B] = b;
        }
        bool operator == (const Color& rhs) {
            return this->values[R] == rhs.red() &&
                    this->values[G] == rhs.green() &&
                    this->values[B] == rhs.blue();
        }
        bool operator != (const Color& rhs) {
            return !(*this == rhs);
        }
};

class Pixel {
    private:
        int x, y;
        Color color = Color();
    public:
        Pixel(int, int);
        Pixel(int, int, uchar, uchar, uchar);
        Pixel(int, int, Color);
        int getX() const;
        int getY() const;
        Color getColor() const;
        void setColor(uchar, uchar, uchar);
        void setColor(Color);
        Pixel neighborN();
        Pixel neighborS();
        Pixel neighborE();
        Pixel neighborW();
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
        Color getPixelColorAt(int, int);
        // 2D Primitives
        void drawLineBresenham(Pixel, Pixel, Color);
        void drawCircle(Pixel, int, Color);
        void drawPolyline(std::vector<Pixel>&, Color);
        void drawPolygon(std::vector<Pixel>&, Color);
        void drawArc(Pixel, Pixel, int, Color);
        // Color Filling algorithms
        void floodFill(Pixel, Color, Color);
};

#endif