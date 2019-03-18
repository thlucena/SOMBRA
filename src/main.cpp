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
    Color background_color = Color(255,255,255);

    if (scene["background_color"] != Json::nullValue) {
        Json::Value b_color = scene["background_color"];
        background_color = Color(b_color["r"].asInt(), b_color["g"].asInt(), b_color["b"].asInt());
    }

    Canvas image_canvas = Canvas(width, height, background_color);
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