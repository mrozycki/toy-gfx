#include "shapes.h"

#include <algorithm>
#include <iostream>

namespace gfx {
namespace shapes {
void rectangle(
        canvas& canvas,
        std::size_t x, std::size_t y,
        std::size_t width, std::size_t height,
        color color) {
    for (auto i = x; i < x + width; ++i) {
        for (auto j = y; j < y + height; ++j) {
            canvas.set_pixel(i, j, color);
        }
    }
}

void circle(canvas& canvas, std::size_t x, std::size_t y, std::size_t r, color color) {
    for (auto i = x - r; i < x + r; ++i) {
        for (auto j = y - r; j < y + r; ++j) {
            if ((j - y) * (j - y) + (i - x) * (i- x) <= r * r) {
                canvas.set_pixel(i, j, color);
            }
        }
    }
}

void line2(canvas& canvas, int x1, int y1, int x2, int y2, color color) {
    if (y1 == y2) {
        for (auto i = x1; i <= x1; ++i) {
            canvas.set_pixel(i, y1, color);
        }
        return;
    } else if (x1 == x2) {
        for (auto i = y1; i <= y1; ++i) {
            canvas.set_pixel(x1, i, color);
        }
        return;
    }

    double a = 1.0 * (y1 - y2) / (x1 - x2);
    double b = y1 - a * x1;
    for (double i = std::min(x1, x2); i < std::max(x1, x2); i += 1.0) {
        for (double j = std::min(y1, y2); j < std::max(y1, y2); j += 1.0) {
            double x1_intercept = a * (i - 0.5) + b;
            double x2_intercept = a * (i + 0.5) + b;
            double y1_intercept = (j - b - 0.5) / a;
            double y2_intercept = (j - b + 0.5) / a;
            if (x1_intercept >= j - 0.5 && x1_intercept <= j + 0.5) {
                canvas.set_pixel(i, j, color);
            } else if (x2_intercept >= j - 0.5 && x2_intercept <= j + 0.5) {
                canvas.set_pixel(i, j, color);
            } else if (y1_intercept >= i - 0.5 && y1_intercept <= i + 0.5) {
                canvas.set_pixel(i, j, color);
            } else if (y2_intercept >= i - 0.5 && y2_intercept <= i + 0.5) {
                canvas.set_pixel(i, j, color);
            }
        }
    }
}

void line(canvas& canvas, int x1, int y1, int x2, int y2, color color) {
    double a = 1.0 * (y1 - y2) / (x1 - x2);
    if (std::abs(a) < 1.0) {
        if (x1 > x2) {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }

        auto y = y1;
        auto dy = 0.0;
        for (auto i = x1; i <= x2; ++i) {
            canvas.set_pixel(i, y, color);
            dy += a;
            if (dy >= 1.0) {
                dy -= 1;
                y += 1;
            } else if (dy <= -1.0) {
                dy += 1;
                y -= 1;
            }
        }
    } else {
        if (y1 > y2) {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }
        auto x = x1;
        auto dx = 0.0;
        for (auto i = y1; i <= y2; ++i) {
            canvas.set_pixel(x, i, color);
            dx += 1.0 / a;
            if (dx >= 1.0) {
                dx -= 1;
                x += 1;
            } else if (dx <= -1.0) {
                dx += 1;
                x -= 1;
            }
        }
    }
}
}
}