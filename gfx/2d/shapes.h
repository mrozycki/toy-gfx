#pragma once

#include "canvas.h"
#include "point.h"

namespace gfx2d {
namespace shapes {
void rectangle(
    canvas& canvas,
    std::size_t x, std::size_t y,
    std::size_t width, std::size_t height,
    color color = color::black);

void circle(
    canvas& canvas, std::size_t x, std::size_t y, std::size_t r, color color = color::black);

void line(canvas& canvas, int x1, int y1, int x2, int y2, color color = color::black);
void line2(canvas& canvas, point a, point b, color color = color::black);

void polygon(canvas& canvas, std::vector<point> const& points, color color = color::black);
void triangle_fill(canvas& canvas, point a, point b, point c, color color = color::black);
}
}