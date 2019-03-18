#include "canvas.h"
#include <algorithm>
#include <fstream>
#include <vector>
#include <iostream>
#include <cmath>
#include <queue>
#define PI 3.14159265

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

Canvas::Canvas(int w, int h, Color color) {
    width = w;
    height = h;
    pixels = std::shared_ptr<uchar[]>(new uchar[width*height*3]);

    for(size_t i = 0; i < width*height*3; i = i + 3) {
       pixels[i] = color.red();
       pixels[i+1] = color.green();
       pixels[i+2] = color.blue();
    }
}

bool Canvas::isValidCoordinate(Pixel point) {
    return point.getX() >= 0 && point.getX() < width && point.getY() >= 0 && point.getY() < height;
}

bool Canvas::isValidCoordinate(int x, int y) {
    return x >= 0 && x < width && y >= 0 && y < height;
}

void Canvas::printToFile(std::string output_file) {
    std::ofstream outfile;
    outfile.open(output_file);
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
    if (!isValidCoordinate(p)) {
        return;
    }
    int p_index = p.getY()*width*3 + p.getX()*3;
    pixels[p_index] = p.getColor().red();
    pixels[p_index + 1] = p.getColor().green();
    pixels[p_index + 2] = p.getColor().blue();
}

void Canvas::drawPixel(int x, int y, Color color) {
    if (!isValidCoordinate(x, y)) {
        return;
    }
    int p_index = y*width*3 + x*3;
    pixels[p_index] = color.red();
    pixels[p_index + 1] = color.green();
    pixels[p_index + 2] = color.blue();
}

Color Canvas::getPixelColorAt(int x, int y) {
    if (!(isValidCoordinate(x, y))) {
        return Color();
    }
    int p_index = y*width*3 + x*3;
    uchar r = pixels[p_index];
    uchar g = pixels[p_index + 1];
    uchar b = pixels[p_index + 2];
    return Color(r, g, b);
}

void Canvas::drawLineBresenham(Pixel start_p, Pixel end_p, Color color) {
    // check if start_p is valid
    if (!isValidCoordinate(start_p)) {
        return;
    }

    // check if end_p is valid
    if (!isValidCoordinate(end_p)) {
        return;
    }

    int delta_Y = end_p.getY() - start_p.getY();
    int delta_X = end_p.getX() - start_p.getX();
    int p_k, x, y;
    
    if ( abs(delta_Y) < abs(delta_X) ) {
        // switch points if not from left to right
        if (start_p.getX() > end_p.getX()) {
            Pixel aux = start_p;
            start_p = end_p;
            end_p = aux;
        }

        delta_X = end_p.getX() - start_p.getX();
        delta_Y = end_p.getY() - start_p.getY();
        int y_i = 1;
        if (delta_Y < 0) {
            y_i = -1;
            delta_Y = -delta_Y;
        }
        p_k = 2*delta_Y - delta_X;
        y = start_p.getY();

        for(x = start_p.getX(); x <= end_p.getX(); x++) {
            drawPixel(x, y, color);
            if (p_k > 0) {
                y = y + y_i;
                p_k = p_k - 2*delta_X;
            }
            p_k = p_k + 2*delta_Y;
        }
        
    } else {
        // switch points if not from bottom to top
        if (start_p.getY() > end_p.getY()) {
            Pixel aux = start_p;
            start_p = end_p;
            end_p = aux;
        }

        delta_X = end_p.getX() - start_p.getX();
        delta_Y = end_p.getY() - start_p.getY();
        int x_i = 1;
        if (delta_X < 0) {
            x_i = -1;
            delta_X = -delta_X;
        }
        p_k = 2*delta_X - delta_Y;
        x = start_p.getX();

        for(y = start_p.getY(); y <= end_p.getY(); y++) {
            drawPixel(x, y, color);
            if (p_k > 0) {
                x = x + x_i;
                p_k = p_k - 2*delta_Y;
            }
            p_k = p_k + 2*delta_X;
        }
    }
}

void Canvas::drawCircle(Pixel center_p, int radius, Color color) {
    // check if center_p is valid
    if (!isValidCoordinate(center_p)) {
        return;
    }
    
    int x = 0;
    int y = radius;
    int d = 1 - radius;
    int delta_E = 3;
    int delta_SE = -2 * radius + 5;

    do {
        drawPixel(center_p.getX() + x, center_p.getY() + y, color);
        drawPixel(center_p.getX() + y, center_p.getY() + x, color);
        drawPixel(center_p.getX() - y, center_p.getY() + x, color);
        drawPixel(center_p.getX() - x, center_p.getY() + y, color);
        drawPixel(center_p.getX() - x, center_p.getY() - y, color);
        drawPixel(center_p.getX() - y, center_p.getY() - x, color);
        drawPixel(center_p.getX() + y, center_p.getY() - x, color);
        drawPixel(center_p.getX() + x, center_p.getY() - y, color);

        if (d < 0) {
            d += delta_E;
            delta_E += 2;
            delta_SE += 2;
        } else {
            d += delta_SE;
            delta_E += 2;
            delta_SE += 4;
            y--;
        }
        x++;
    } while (y >= x);    
}

void Canvas::drawPolyline(std::vector<Pixel>& points, Color color) {
    if (points.size() < 2) {
        return;
    }

    for(size_t i = 0; i < points.size(); i++) {
        if (!isValidCoordinate(points[i])) {
            return;
        }
    }

    for(size_t i = 0; i < points.size() - 1; i++) {
        drawLineBresenham(points[i], points[i+1], color);
    }
}

void Canvas::drawPolygon(std::vector<Pixel>& points, Color color) {
    if (points.size() < 3) {
        return;
    }

    for(size_t i = 0; i < points.size(); i++) {
        if (!isValidCoordinate(points[i])) {
            return;
        }
    }

    for(size_t i = 0; i < points.size() - 1; i++) {
        drawLineBresenham(points[i], points[i+1], color);
    }
    drawLineBresenham(points[points.size() - 1], points[0], color);
}

int Canvas::calcAngle(int x_1, int y_1, int x_2, int y_2) {
    double dot = x_1*x_2 + y_1*y_2;
    double det = x_1*y_2 - y_1*x_2;
    int angle = static_cast<int>(std::atan2(det, dot) * 180 / PI);
    if (angle < 0) { angle += 360; };
    return angle;
}

void Canvas::drawArc(Pixel center_p, Pixel start_p, int angle, Color color) {
    if (!isValidCoordinate(center_p)) {
        return;
    }

    if (!isValidCoordinate(start_p)) {
        return;
    }

    if (center_p == start_p) {
        return;
    }

    if (angle <= 0) {
        return;
    }

    int s_1 = start_p.getX() - center_p.getX();
    int s_2 = start_p.getY() - center_p.getY();
    double radius_double = sqrt( pow(s_1, 2) + pow(s_2, 2));
    int radius = static_cast<int>(round(radius_double));

    if (angle >= 360) {
        drawCircle(center_p, radius, color);
    }

    ///////////////////////////////////////

    // vector obtained from start_p, considering the center_p as the point (0,0)
    int vector_x = start_p.getX() - center_p.getX();
    int vector_y = start_p.getY() - center_p.getY();

    int x = 0;
    int y = radius;
    int d = 1 - radius;
    int delta_E = 3;
    int delta_SE = -2 * radius + 5;

    do {
        if (calcAngle(x, y, vector_x, vector_y) <= angle) {
            drawPixel(center_p.getX() + x, center_p.getY() + y, color);
        }
        if (calcAngle(y, x, vector_x, vector_y) <= angle) {
            drawPixel(center_p.getX() + y, center_p.getY() + x, color);
        }
        if (calcAngle(-y, x, vector_x, vector_y) <= angle) {
            drawPixel(center_p.getX() - y, center_p.getY() + x, color);
        }
        if (calcAngle(-x, y, vector_x, vector_y) <= angle) {
            drawPixel(center_p.getX() - x, center_p.getY() + y, color);
        }
        if (calcAngle(-x, -y, vector_x, vector_y) <= angle) {
            drawPixel(center_p.getX() - x, center_p.getY() - y, color);
        }
        if (calcAngle(-y, -x, vector_x, vector_y) <= angle) {
            drawPixel(center_p.getX() - y, center_p.getY() - x, color);
        }
        if (calcAngle(y, -x, vector_x, vector_y) <= angle) {
            drawPixel(center_p.getX() + y, center_p.getY() - x, color);
        }
        if (calcAngle(x, -y, vector_x, vector_y) <= angle) {
            drawPixel(center_p.getX() + x, center_p.getY() - y, color); 
        }

        if (d < 0) {
            d += delta_E;
            delta_E += 2;
            delta_SE += 2;
        } else {
            d += delta_SE;
            delta_E += 2;
            delta_SE += 4;
            y--;
        }
        x++;
    } while (y >= x);

}

void Canvas::floodFill(Pixel seed_p, Color replacement_color) {
    if (!isValidCoordinate(seed_p)) {
        return;
    }

    Color target_color = getPixelColorAt(seed_p.getX(), seed_p.getY());
    if (target_color == replacement_color) {
        return;
    }

    std::queue<Pixel> to_print;
    to_print.push( Pixel(seed_p.getX(), seed_p.getY(), replacement_color) );

    do {
        seed_p = to_print.front();
        to_print.pop();

        if (!isValidCoordinate(seed_p)) {
            continue;
        }

        if (getPixelColorAt(seed_p.getX(), seed_p.getY()) != target_color) {
            continue;
        }

        drawPixel(seed_p.getX(), seed_p.getY(), replacement_color);
        to_print.push(seed_p.neighborN());
        to_print.push(seed_p.neighborE());
        to_print.push(seed_p.neighborS());
        to_print.push(seed_p.neighborW());

    } while (to_print.size() > 0);
}

void Canvas::applyAntiAlias() {
    uchar *new_pixels = new uchar[width*height*3];

    // Filling first and last rows
    for(int i = 0; i < width; i++) {
        /* code */
        int i_first_row = i*width*3 + 0*3;
        int i_last_row = i*width*3 + (height-1)*3;
        new_pixels[i_first_row] = pixels[i_first_row];
        new_pixels[i_first_row + 1] = pixels[i_first_row + 1];
        new_pixels[i_first_row + 2] = pixels[i_first_row + 2];
        new_pixels[i_last_row] = pixels[i_last_row];
        new_pixels[i_last_row + 1] = pixels[i_last_row + 1];
        new_pixels[i_last_row + 2] = pixels[i_last_row + 2];
    }

    // Filling first and last columns
    for(int i = 1; i < height - 1; i++) {
        /* code */
        int i_first_row = 0*width*3 + i*3;
        int i_last_row = (width-1)*width*3 + i*3;
        new_pixels[i_first_row] = pixels[i_first_row];
        new_pixels[i_first_row + 1] = pixels[i_first_row + 1];
        new_pixels[i_first_row + 2] = pixels[i_first_row + 2];
        new_pixels[i_last_row] = pixels[i_last_row];
        new_pixels[i_last_row + 1] = pixels[i_last_row + 1];
        new_pixels[i_last_row + 2] = pixels[i_last_row + 2];
    }

    double sum_R, sum_G, sum_B;
    int weights[] = {1, 2, 1, 2, 4, 2, 1, 2, 1};
    Color aux_c;
    int neighbor_i;

    for(int x = 1; x < width - 1; x++) {
        for(int y = 1; y < height - 1; y++) {
            sum_R = 0;
            sum_G = 0;
            sum_B = 0;
            neighbor_i = 0;
            for (int x_offset = -1; x_offset <= 1; x_offset++) {
                for (int y_offset = -1; y_offset <= 1; y_offset++) {
                    aux_c = getPixelColorAt(x + x_offset, y + y_offset);
                    sum_R += aux_c.red() * weights[neighbor_i];
                    sum_G += aux_c.green() * weights[neighbor_i];
                    sum_B += aux_c.blue() * weights[neighbor_i];
                    neighbor_i++;
                }
            }

            int p_index = y*width*3 + x*3;
            new_pixels[p_index] = static_cast<uchar>(round(sum_R / 16));
            new_pixels[p_index + 1] = static_cast<uchar>(round(sum_G / 16));
            new_pixels[p_index + 2] = static_cast<uchar>(round(sum_B / 16));
        }
    }
    
    pixels = std::shared_ptr<uchar[]>(new_pixels);
}