#include <iostream>

#include <cmath>

#include "gfx/canvas.h"
#include "gfx/shapes.h"

int main() {
    gfx::canvas canvas(800, 800);
    for (double alpha = 0.0; alpha < 6.28; alpha += 0.05) {
        gfx::shapes::line(canvas, 400 + (int)floor(400*sin(alpha)), 400 + (int)floor(400*cos(alpha)), 400, 400);
    }
    print_to_file(canvas, "test.pbm");

    gfx::canvas canvas2(800, 800);
    for (double alpha = 0.0; alpha < 6.28; alpha += 0.05) {
        gfx::shapes::line2(canvas, 400 + (int)floor(400*sin(alpha)), 400 + (int)floor(400*cos(alpha)), 400, 400);
    }
    print_to_file(canvas, "test2.pbm");

    return 0;
}