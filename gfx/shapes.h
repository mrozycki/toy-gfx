#pragma once

#include "canvas.h"

namespace gfx {
namespace shapes {
void rectangle(
    canvas& canvas,
    std::size_t x, std::size_t y,
    std::size_t width, std::size_t height,
    color color = color::black);

void circle(
    canvas& canvas, std::size_t x, std::size_t y, std::size_t r, color color = color::black);

void line(canvas& canvas, int x1, int y1, int x2, int y2, color color = color::black);
void line2(canvas& canvas, int x1, int y1, int x2, int y2, color color = color::black);
}
}