#include "canvas.h"

#include <fstream>

namespace gfx2d {
canvas::canvas(std::size_t width, std::size_t height, color background)
    : width_(width)
    , height_(height)
    , pixels_(width_ * height_, {background, std::numeric_limits<double>::infinity()})
    , background_(background) { }

void canvas::set_pixel(std::size_t x, std::size_t y, pixel p) {
    if (x >= 0 && x < width_ && y >= 0 && y < height_ && p.depth < get_pixel(x, y).depth) {
        pixels_[y * width_ + x] = p;
    }
}

void canvas::set_color(std::size_t x, std::size_t y, color c) {
    if (x >= 0 && x < width_ && y >= 0 && y < height_) {
        pixels_[y * width_ + x] = {c, std::numeric_limits<double>::infinity()};
    }
}

pixel canvas::get_pixel(std::size_t x, std::size_t y) const {
    return pixels_[y * width_ + x];
}

void canvas::clear() {
    for (auto& pixel : pixels_) {
        pixel = {background_, std::numeric_limits<double>::infinity()};
    }
}

void canvas::subsample(std::size_t rate, canvas& dest) const {
    for (int y = 0; y < height_/rate; ++y) {
        for (int x = 0; x < width_/rate; ++x) {
            int r = 0, g = 0, b = 0;
            for (int j = 0; j < rate; ++j) {
                for (int i = 0; i < rate; ++i) {
                    auto const color = get_pixel(x * rate + i, y * rate + j).c;
                    r += color.red;
                    g += color.green;
                    b += color.blue;
                }
            }
            dest.set_color(x, y, { 
                static_cast<uint8_t>(r / rate / rate), 
                static_cast<uint8_t>(g / rate / rate), 
                static_cast<uint8_t>(b / rate / rate) 
            });
        }
    }
}

void print_to_file(canvas const& canvas, std::string const& filename) {
    std::fstream file(filename, std::ios::out);
    file << "P6 " << canvas.width() << " " << canvas.height() << " 255\n";
    for (auto y = 0; y < canvas.height(); ++y) {
        for (auto x = 0; x < canvas.width(); ++x) {
            auto const pixel = canvas.get_pixel(x, y);
            file << pixel.c.red << pixel.c.green << pixel.c.blue;
        }
    }
}
}