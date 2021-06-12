#pragma once

#include <vector>
#include "gfx/2d/canvas.h"

namespace gfx3d {
struct point {
    double x, y, z;
};

struct face {
    point a, b, c;
};

class object {
public:
    object(std::vector<face> faces) : faces_(std::move(faces)) {}

    void render(gfx2d::canvas& canvas) const;
    void rotate_y(double alpha);

    std::vector<face> const& faces() const { return faces_; }

private:
    std::vector<face> faces_;
};

object load_from_obj(std::string const& filename);
}