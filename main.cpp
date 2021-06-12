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

int main() {
    gfx2d::canvas canvas(800, 800);

    /*
    int i = 0;
    auto object = gfx3d::load_from_obj("suzanne.obj");
    for (auto const& face : object.faces()) {
        gfx2d::point a{static_cast<int>((face.a.x + 2) * 200), static_cast<int>((-face.a.y + 2) * 200)};
        gfx2d::point b{static_cast<int>((face.b.x + 2) * 200), static_cast<int>((-face.b.y + 2) * 200)};
        gfx2d::point c{static_cast<int>((face.c.x + 2) * 200), static_cast<int>((-face.c.y + 2) * 200)};

        canvas.clear();
        gfx2d::shapes::polygon(canvas, {a, b, c});
        print_to_file(canvas, create_filename("suzanne/triangle_", 10*i));

        canvas.clear();
        gfx2d::shapes::triangle_fill(canvas, a, b, c);
        print_to_file(canvas, create_filename("suzanne/triangle_", 10*i+1));
        ++i;
    }

    print_to_file(canvas, "suzanne.pbm");
    */

    auto object = gfx3d::load_from_obj("suzanne.obj");
    const int number_of_frames = 200;
    for (int i = 0; i < number_of_frames; ++i) {
        if (i % 10 == 9) std::cout << "." << std::flush;
        if (i % 100 == 99) std::cout << std::endl;
        gfx2d::shapes::rectangle(canvas, 0, 0, 800, 800, gfx2d::color{0, 0, 128});
        auto rotated_object = object;
        rotated_object.rotate_y(6.28 / number_of_frames * i);
        rotated_object.render(canvas);
        print_to_file(canvas, create_filename("suzanne/frame_", i));
    }

    return 0;
}