#include "shapes.h"

#include <algorithm>
#include <iostream>

namespace gfx2d {
namespace shapes {
void rectangle(
        canvas& canvas,
        std::size_t x, std::size_t y,
        std::size_t width, std::size_t height,
        color color) {
    for (auto i = x; i < x + width; ++i) {
        for (auto j = y; j < y + height; ++j) {
            canvas.set_color(i, j, color);
        }
    }
}

void circle(canvas& canvas, std::size_t x, std::size_t y, std::size_t r, color color) {
    for (auto i = x - r; i < x + r; ++i) {
        for (auto j = y - r; j < y + r; ++j) {
            if ((j - y) * (j - y) + (i - x) * (i- x) <= r * r) {
                canvas.set_color(i, j, color);
            }
        }
    }
}

void line2(canvas& canvas, int x1, int y1, int x2, int y2, color color) {
    if (y1 == y2) {
        for (auto i = x1; i <= x1; ++i) {
            canvas.set_color(i, y1, color);
        }
        return;
    } else if (x1 == x2) {
        for (auto i = y1; i <= y1; ++i) {
            canvas.set_color(x1, i, color);
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
                canvas.set_color(i, j, color);
            } else if (x2_intercept >= j - 0.5 && x2_intercept <= j + 0.5) {
                canvas.set_color(i, j, color);
            } else if (y1_intercept >= i - 0.5 && y1_intercept <= i + 0.5) {
                canvas.set_color(i, j, color);
            } else if (y2_intercept >= i - 0.5 && y2_intercept <= i + 0.5) {
                canvas.set_color(i, j, color);
            }
        }
    }
}

void line(canvas& canvas, point a, point b, color color) {
    double gradient = 1.0 * (a.y - b.y) / (a.x - b.x);
    if (std::abs(gradient) < 1.0) {
        if (a.x > b.x) {
            std::swap(a.x, b.x);
            std::swap(a.y, b.y);
        }

        auto y = a.y;
        auto dy = 0.0;
        for (auto i = a.x; i <= b.x; ++i) {
            canvas.set_color(i, y, color);
            dy += gradient;
            if (dy >= 1.0) {
                dy -= 1;
                y += 1;
            } else if (dy <= -1.0) {
                dy += 1;
                y -= 1;
            }
        }
    } else {
        if (a.y > b.y) {
            std::swap(a.x, b.x);
            std::swap(a.y, b.y);
        }
        auto x = a.x;
        auto dx = 0.0;
        for (auto i = a.y; i <= b.y; ++i) {
            canvas.set_color(x, i, color);
            dx += 1.0 / gradient;
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

void polygon(canvas& canvas, std::vector<point> const& points, color color) {
    for (std::size_t i = 0; i+1 < points.size(); ++i) {
        line(canvas, points[i], points[i+1], color);
    }
    line(canvas, points[points.size()-1], points[0], color);
}

void triangle_fill(canvas& canvas, point a, point b, point c, color color) {
    if (a.y > b.y) {
        std::swap(a, b);
    }
    if (a.y > c.y) {
        std::swap(a, c);
    }
    if (b.y > c.y) {
        std::swap(b, c);
    }

    double start_x = a.x;
    double end_x = a.x;
    double start_z = a.z;
    double end_z = a.z;
    int y = a.y;
    if (a.y != b.y) {
        double start_dx = 1.0 * (b.x - start_x) / (b.y - y);
        double end_dx = 1.0 * (c.x - start_x) / (c.y - y);
        if (start_dx > end_dx) {
            std::swap(start_dx, end_dx);
            std::swap(b, c);
        }
        double start_dz = 1.0 * (b.z - start_z) / (b.y - y);
        double end_dz = 1.0 * (c.z - end_z) / (c.y - y);
        for (; y < std::min(b.y, c.y); ++y) {
            double dz_dx = (end_z - start_z) / (end_x - start_x);
            double z = start_z;
            for (int x = start_x; x <= end_x; ++x, z += dz_dx) {
                canvas.set_pixel(x, y, {color, z});
            }
            start_x += start_dx;
            end_x += end_dx;
            start_z += start_dz;
            end_z += end_dz;
        }
    } else {
        if (a.x > b.x) {
            std::swap(a, b);
        }
        start_x = a.x;
        end_x = b.x;
        start_z = a.z;
        end_z = b.z;
    }

    auto const d = (b.y > c.y) ? b : c;
    double start_dx = 1.0 * (d.x - start_x) / (d.y - y);
    double end_dx = 1.0 * (d.x - end_x) / (d.y - y);
    double start_dz = 1.0 * (d.z - start_z) / (d.y - y);
    double end_dz = 1.0 * (d.z - end_z) / (d.y - y);

    for (; y <= d.y; ++y) {
        double dz_dx = (end_z - start_z) / (end_x - start_x);
        double z = start_z;
        for (int x = start_x; x <= end_x; ++x, z += dz_dx) {
            canvas.set_pixel(x, y, {color, z});
        }
        start_x += start_dx;
        end_x += end_dx;
        start_z += start_dz;
        end_z += end_dz;
    }
}
}
}