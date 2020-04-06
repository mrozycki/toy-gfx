#include <iostream>

#include <cmath>

#include "gfx/2d/canvas.h"
#include "gfx/2d/shapes.h"

int main() {
    gfx2d::canvas canvas(800, 800);

    gfx2d::shapes::polygon(canvas, {{100, 100}, {100, 200}, {200, 200}, {200, 100}});
    gfx2d::shapes::polygon(canvas, {{200, 400}, {600, 600}, {400, 400}, {600, 200}});

    print_to_file(canvas, "test.pbm");

    return 0;
}