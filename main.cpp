#include <iostream>

#include "gfx/canvas.h"

int main() {
    gfx::canvas canvas(100, 100);
    for (auto i = 0; i < 50; ++i) {
        for (auto j = 0; j < 50; ++j) {
            canvas.set_pixel(i, j, gfx::color::black);
        }
    }

    for (auto i = 50; i < 100; ++i) {
        for (auto j = 50; j < 100; ++j) {
            canvas.set_pixel(i, j, gfx::color::black);
        }
    }
    print_to_file(canvas, "test.pbm");

    return 0;
}