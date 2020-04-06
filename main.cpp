#include <iostream>

#include <cmath>

#include "gfx/canvas.h"
#include "gfx/shapes.h"

int main() {
    gfx::canvas canvas(800, 800);

    gfx::shapes::polygon(canvas, {{100, 100}, {100, 200}, {200, 200}, {200, 100}});
    gfx::shapes::polygon(canvas, {{200, 400}, {600, 600}, {400, 400}, {600, 200}});

    print_to_file(canvas, "test.pbm");

    return 0;
}