#include <iostream>
#include <iomanip>
#include <sstream>

#include <cmath>

#include "gfx/2d/canvas.h"
#include "gfx/2d/point.h"
#include "gfx/2d/shapes.h"
#include "gfx/3d/object.h"

std::string create_filename(std::string const& prefix, int n) {
    std::stringstream ss;
    ss << prefix << std::setw(4) << std::setfill('0') << n << ".ppm";
    return ss.str();
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <obj_name> [<size>]\n";
        return -1;
    }

    std::string object_name = argv[1];
    auto const canvas_size = [&] {
        if (argc == 3) {
            return std::atoi(argv[2]);
        } else {
            return 400;
        }
    }();
    gfx2d::canvas canvas(canvas_size, canvas_size);

    auto object = gfx3d::load_from_obj(object_name + ".obj");
    const int number_of_frames = 200;
    for (int i = 0; i < number_of_frames; ++i) {
        if (i % 10 == 9) std::cout << "." << std::flush;
        if (i % 100 == 99) std::cout << std::endl;
        gfx2d::shapes::rectangle(canvas, 0, 0, canvas_size, canvas_size, gfx2d::color{0, 0, 128});
        auto rotated_object = object;
        rotated_object.rotate_y(6.28 / number_of_frames * i);
        rotated_object.render(canvas);
        print_to_file(canvas, create_filename("render/" + object_name + "/frame_", i));
    }

    return 0;
}