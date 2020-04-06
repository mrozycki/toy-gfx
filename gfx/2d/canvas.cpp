#include "canvas.h"

#include <fstream>

namespace gfx2d {
canvas::canvas(std::size_t width, std::size_t height, color background)
    : width_(width)
    , height_(height)
    , pixels_(width_ * height_, background) { }

void canvas::set_pixel(std::size_t x, std::size_t y, color c) {
    if (x >= 0 && x < width_ && y >= 0 && y < height_) {
        pixels_[y * width_ + x] = c;
    }
}

color canvas::get_pixel(std::size_t x, std::size_t y) const {
    return pixels_[y * width_ + x];
}

void print_to_file(canvas const& canvas, std::string const& filename) {
    std::fstream file(filename, std::ios::out);
    file << "P1 " << canvas.width() << " " << canvas.height() << "\n";
    for (auto y = 0; y < canvas.height(); ++y) {
        for (auto x = 0; x < canvas.width(); ++x) {
            if (canvas.get_pixel(x, y) == color::white) {
                file << "0 ";
            } else {
                file << "1 ";
            }
        }
        file << "\n";
    }
}
}