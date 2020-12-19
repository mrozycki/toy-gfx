#include <iostream>
#include <iomanip>
#include <sstream>

#include <cmath>

#include "gfx/2d/canvas.h"
#include "gfx/2d/shapes.h"
#include "gfx/3d/object.h"

std::string create_filename(std::string const& prefix, int n) {
    std::stringstream ss;
    ss << prefix << std::setw(3) << std::setfill('0') << n << ".pbm";
    return ss.str();
}

int main() {
    gfx2d::canvas canvas(800, 800);
    auto object = gfx3d::load_from_obj("suzanne.obj");

    const int number_of_frames = 200;
    for (int i = 0; i < number_of_frames; ++i) {
        if (i % 10 == 0) std::cout << "." << std::flush;
        if (i % 100 == 0) std::cout << std::endl;
        gfx2d::shapes::rectangle(canvas, 0, 0, 800, 800, gfx2d::color::white);
        auto rotated_object = object;
        rotated_object.rotate_y(6.28 / number_of_frames * i);
        rotated_object.render(canvas);
        print_to_file(canvas, create_filename("suzanne/frame_", i));
    }

    return 0;
}