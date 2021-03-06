#pragma once

#include <vector>
#include <string>

namespace gfx2d {
struct color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    color dim(double factor) const {
        return { 
            static_cast<uint8_t>(red * factor), 
            static_cast<uint8_t>(green * factor), 
            static_cast<uint8_t>(blue * factor)
        };
    }
};

namespace colors {
constexpr color WHITE{255, 255, 255};
constexpr color BLACK{0, 0, 0};
constexpr color RED{255, 0, 0};
constexpr color GREEN{0, 255, 0};
constexpr color BLUE{0, 0, 255};
}

struct pixel {
    color c;
    double depth;
};

class canvas {
public:
    canvas(std::size_t width, std::size_t height, color background = colors::WHITE);

    void set_pixel(std::size_t x, std::size_t y, pixel c);
    void set_color(std::size_t x, std::size_t y, color c);
    pixel get_pixel(std::size_t x, std::size_t y) const;
    void clear();

    std::size_t width() const { return width_; }
    std::size_t height() const { return height_; }

    void subsample(std::size_t rate, canvas& dest) const;

private:
    std::size_t width_, height_;
    std::vector<pixel> pixels_;
    color background_;
};

void print_to_file(canvas const& canvas, std::string const& filename);
}