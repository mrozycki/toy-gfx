#pragma once

#include <vector>
#include <string>

namespace gfx2d {
struct color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

namespace colors {
constexpr color WHITE{255, 255, 255};
constexpr color BLACK{0, 0, 0};
constexpr color RED{255, 0, 0};
constexpr color GREEN{0, 255, 0};
constexpr color BLUE{0, 0, 255};
}

class canvas {
public:
    canvas(std::size_t width, std::size_t height, color background = colors::WHITE);

    void set_pixel(std::size_t x, std::size_t y, color c);
    color get_pixel(std::size_t x, std::size_t y) const;
    void clear();

    std::size_t width() const { return width_; }
    std::size_t height() const { return height_; }

private:
    std::size_t width_, height_;
    std::vector<color> pixels_;
    color background_;
};

void print_to_file(canvas const& canvas, std::string const& filename);
}