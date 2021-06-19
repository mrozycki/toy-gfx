#pragma once

#include <vector>
#include <cmath>

#include "gfx/2d/canvas.h"

namespace gfx3d {
struct point {
    double x, y, z;
    
    double distance() const {
        return std::sqrt(x*x + y*y + z*z);
    }
};

struct face {
    point a, b, c;
};

class object {
public:
    object(std::vector<face> faces, double radius) 
        : faces_(std::move(faces))
        , radius_(radius) {}

    void render(gfx2d::canvas& canvas) const;
    void rotate_y(double alpha);

    std::vector<face> const& faces() const { return faces_; }

private:
    std::vector<face> faces_;
    double radius_;
};

object load_from_obj(std::string const& filename);
}