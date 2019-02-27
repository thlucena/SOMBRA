#include "canvas.h"
#include <algorithm>
#include <fstream>

Canvas::Canvas() {
    width = 800;
    height = 600;
    pixels = std::shared_ptr<uchar[]>(new uchar[width*height*3]);
    std::fill(pixels.get(), pixels.get() + (width * height * 3), 255);
}

Canvas::Canvas(int w, int h) {
    width = w;
    height = h;
    pixels = std::shared_ptr<uchar[]>(new uchar[width*height*3]);
    std::fill(pixels.get(), pixels.get() + (width * height * 3), 255);
}

void Canvas::printToFile() {
    std::ofstream outfile;
    outfile.open("canvas.ppm");
    outfile << "P3" << std::endl;
    outfile << width << " " << height << std::endl;
    outfile << "255" << std::endl;
    auto line_end = width*3;
    for (auto i = 0; i < (height*width*3); ++i) {
        outfile << int(pixels[i]) << " ";
        if (i % line_end == line_end - 1) { outfile << std::endl; }  
    }
    outfile.close();
}

void Canvas::drawPoint(Point p) {
    if (p.getX() < 0 || p.getX() > width || p.getY() < 0 || p.getY() > height) {
        return;
    }
    int p_index = p.getX()*width*3 + p.getY()*3;
    pixels[p_index] = p.getColor().red();
    pixels[p_index + 1] = p.getColor().green();
    pixels[p_index + 2] = p.getColor().blue();
}