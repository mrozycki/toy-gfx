#include <iostream>

#include <cmath>

#include "gfx/2d/canvas.h"
#include "gfx/2d/shapes.h"
#include "gfx/3d/object.h"

int main() {
    gfx2d::canvas canvas(800, 800);
    auto object = gfx3d::load_from_obj("suzanne.obj");
    object.render(canvas);

    print_to_file(canvas, "test.pbm");

    return 0;
}