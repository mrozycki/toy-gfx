#pragma once

#include <vector>
#include <string>

namespace gfx2d {
enum class color {
    white, black
};

class canvas {
public:
    canvas(std::size_t width, std::size_t height, color background = color::white);

    void set_pixel(std::size_t x, std::size_t y, color c);
    color get_pixel(std::size_t x, std::size_t y) const;

    std::size_t width() const { return width_; }
    std::size_t height() const { return height_; }

private:
    std::size_t width_, height_;
    std::vector<color> pixels_;
};

void print_to_file(canvas const& canvas, std::string const& filename);
}