#include "canvas.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <json/json.h>

void processSceneFile(std::string scene_file, std::string output_file) {
    std::ifstream infile(scene_file);
    if(!infile) {
        std::cout << ">>> Unable to open scene description file!" << std::endl;
        return;
    }

    Json::Value scene;
    infile >> scene;
    infile.close();

    if (scene["width"] == Json::nullValue || scene["height"] == Json::nullValue) {
        std::cout << ">>> Scene description must provide width and height!" << std::endl;
        return;
    }

    int width = scene["width"].asInt();
    int height = scene["height"].asInt();
    Canvas image_canvas = Canvas(width, height);

    // Color-palette
    if (scene["color_palette"] != Json::nullValue) {
        for(int i = 0; i < scene["color_palette"].size(); i++) {
            auto color_p_obj = scene["color_palette"][i];
            Color color = Color(color_p_obj["r"].asInt(), color_p_obj["g"].asInt(), color_p_obj["b"].asInt());
            image_canvas.addToPalette(color_p_obj["name"].asString(), color);
        }
    }

    // Background color
    if (scene["background_color"] != Json::nullValue) {
        auto b_color_obj = scene["background_color"];
        Color* b_color = image_canvas.getColorFromObj(b_color_obj);
        if (b_color == nullptr) {
            std::cout << ">>> '" << b_color_obj["name"].asString() << "' color not defined on palette!" << std::endl;
            return;
        }
        image_canvas.setBackground(*b_color);
    }


    // Parsing objects
    if (scene["objects"] != Json::nullValue) {
        for(int i = 0; i < scene["objects"].size(); i++) {
            auto object = scene["objects"][i];

            if(object["type"] == Json::nullValue) {
                std::cout << ">>> Object " << i << " of objects array doesn't have a type value!" << std::endl;
                return;
            }

            // Line
            if(object["type"] == "line") {
                Pixel start_p = Pixel(object["start_point"]["x"].asInt(), object["start_point"]["y"].asInt());
                Pixel end_p = Pixel(object["end_point"]["x"].asInt(), object["end_point"]["y"].asInt());
                // Color color = Color(object["color"]["r"].asInt(), object["color"]["g"].asInt(), object["color"]["b"].asInt());

                auto color_obj = object["color"];
                Color* color = image_canvas.getColorFromObj(color_obj);
                if (color == nullptr) {
                    std::cout << ">>> '" << color_obj["name"].asString() << "' color not defined on palette!" << std::endl;
                    return;
                }

                image_canvas.drawLineBresenham(start_p, end_p, *color);
                continue;
            }

            // Circle
            if(object["type"] == "circle") {
                Pixel center_p = Pixel(object["center_point"]["x"].asInt(), object["center_point"]["y"].asInt());
                int radius = object["radius"].asInt();
                // Color color = Color(object["color"]["r"].asInt(), object["color"]["g"].asInt(), object["color"]["b"].asInt());
                auto color_obj = object["color"];
                Color* color = image_canvas.getColorFromObj(color_obj);
                if (color == nullptr) {
                    std::cout << ">>> '" << color_obj["name"].asString() << "' color not defined on palette!" << std::endl;
                    return;
                }

                image_canvas.drawCircle(center_p, radius, *color);
                continue;
            }

            // Arc
            if(object["type"] == "arc") {
                Pixel center_p = Pixel(object["center_point"]["x"].asInt(), object["center_point"]["y"].asInt());
                Pixel start_p = Pixel(object["start_point"]["x"].asInt(), object["start_point"]["y"].asInt());
                int angle = object["angle"].asInt();
                // Color color = Color(object["color"]["r"].asInt(), object["color"]["g"].asInt(), object["color"]["b"].asInt());
                auto color_obj = object["color"];
                Color* color = image_canvas.getColorFromObj(color_obj);
                if (color == nullptr) {
                    std::cout << ">>> '" << color_obj["name"].asString() << "' color not defined on palette!" << std::endl;
                    return;
                }
                image_canvas.drawArc(center_p, start_p, angle, *color);
                continue;
            }

            // Polyline and polygon
            if (object["type"] == "polyline" || object["type"] == "polygon") {
                std::vector<Pixel> points;
                for(int i = 0; i < object["points"].size(); i++) {
                    auto point = object["points"][i];
                    points.push_back(Pixel(point["x"].asInt(), point["y"].asInt()));
                }
                // Color color = Color(object["color"]["r"].asInt(), object["color"]["g"].asInt(), object["color"]["b"].asInt());

                auto color_obj = object["color"];
                Color* color = image_canvas.getColorFromObj(color_obj);
                if (color == nullptr) {
                    std::cout << ">>> '" << color_obj["name"].asString() << "' color not defined on palette!" << std::endl;
                    return;
                }

                if (object["type"] == "polyline") {
                    image_canvas.drawPolyline(points, *color);
                } else {
                    image_canvas.drawPolygon(points, *color);
                }
                
                continue;
            }            
        }
    }

    // Parsing color fills
    if (scene["color_fills"] != Json::nullValue) {
        for(int i = 0; i < scene["color_fills"].size(); i++) {
            auto seed_obj = scene["color_fills"][i]["seed"];
            auto color_obj = scene["color_fills"][i]["color"];

            Pixel seed_p = Pixel(seed_obj["x"].asInt(), seed_obj["y"].asInt());
            // Color color = Color(color_obj["r"].asInt(), color_obj["g"].asInt(), color_obj["b"].asInt());
            // auto color_obj = object["color"];
            Color* color = image_canvas.getColorFromObj(color_obj);
            if (color == nullptr) {
                std::cout << ">>> '" << color_obj["name"].asString() << "' color not defined on palette!" << std::endl;
                return;
            }
            image_canvas.floodFill(seed_p, *color);
        }
    }

    // Parsing anti-alias option
    if (scene["anti_alias"] != Json::nullValue && scene["anti_alias"] == "on") {
        image_canvas.applyAntiAlias();
    }
    
    image_canvas.printToFile(output_file);
}

int main(int argc, char** argv) {
    if (argc > 2) {
        std::string scene_file = argv[1];
        std::string image_out_file = argv[2];

        // Check scene file extension
        size_t img_index;
        std::string scene_file_extension = scene_file;
        img_index = scene_file.rfind('.', scene_file.length());
        scene_file_extension = scene_file.substr(img_index+1, scene_file.length() - img_index);
        if (scene_file_extension != "json") {
            std::cout << "Scene description file must have JSON extension!" << std::endl;
            return EXIT_FAILURE;
        }

        // Check image output file extension
        std::string out_file_extension = image_out_file;
        img_index = image_out_file.rfind('.', image_out_file.length());
        out_file_extension = image_out_file.substr(img_index+1, image_out_file.length() - img_index);
        if (out_file_extension != "ppm") {
            std::cout << "Image output file must have PPM extension!" << std::endl;
            return EXIT_FAILURE;
        }

        processSceneFile(scene_file, image_out_file);        
    } else {
        std::cout << "You must provide a scene description file and an output file name!" << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}