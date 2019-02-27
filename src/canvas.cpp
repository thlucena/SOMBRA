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

void Canvas::drawPixel(Pixel p) {
    if (p.getX() < 0 || p.getX() > width || p.getY() < 0 || p.getY() > height) {
        return;
    }
    int p_index = p.getY()*width*3 + p.getX()*3;
    pixels[p_index] = p.getColor().red();
    pixels[p_index + 1] = p.getColor().green();
    pixels[p_index + 2] = p.getColor().blue();
}

void Canvas::drawPixel(int x, int y, Color color) {
    if (x < 0 || x > width || y < 0 || y > height) {
        return;
    }
    int p_index = y*width*3 + x*3;
    pixels[p_index] = color.red();
    pixels[p_index + 1] = color.green();
    pixels[p_index + 2] = color.blue();
}

void Canvas::drawLineBresenham(Pixel start_p, Pixel end_p, Color color) {
    // check if start_p is valid
    if (start_p.getX() < 0 || start_p.getX() > width || start_p.getY() < 0 || start_p.getY() > height) {
        return;
    }

    // check if end_p is valid
    if (end_p.getX() < 0 || end_p.getX() > width || end_p.getY() < 0 || end_p.getY() > height) {
        return;
    }

    // switch points if not from left to right
    if (start_p.getX() > end_p.getX()) {
        Pixel aux = start_p;
        start_p = end_p;
        end_p = aux;
    }

    int delta_X = end_p.getX() - start_p.getX();
    int delta_Y = end_p.getY() - start_p.getY();
    double m = delta_Y / delta_X;

    int p_k, x, y, end_x, end_y;
    x = start_p.getX();
    y = start_p.getY();
    end_x = end_p.getX();
    end_y = end_p.getY();

    drawPixel(x, y, color);

    if (-1 <= m <= 1) {
        // x always increase
        // y coordinate might not change
        int y_i, p_k;
        if (m >= 0) { 
            y_i = -1; // increasing line
            delta_Y = -delta_Y; 
        } else {
            y_i = 1; // decreasing line
        }
        p_k = 2*delta_Y - delta_X;

        for(x = x+1; x < end_x; x++) {
            p_k = p_k + 2*delta_Y;
            if (p_k > 0) {
                y = y + y_i;
                p_k = p_k - 2*delta_X;
            }
            drawPixel(x, y, color);
        }
    } else {
        // y always increase
        // x coordinate might not change
        int x_i, p_k;
        if (m > 0) { 
            x_i = 1; // increasing line
        } else {
            x_i = -1; // decreasing line
            delta_X = -delta_X; 
        }
        p_k = 2*delta_X - delta_Y;

        for(y = y+1; y < end_y; y++) {
            p_k = p_k + 2*delta_X;
            if (p_k > 0) {
                x = x + x_i;
                p_k = p_k - 2*delta_Y;
            }
            drawPixel(x, y, color);
        }
    }
}