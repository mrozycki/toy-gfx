#pragma once

#include <vector>
#include <cmath>

#include "gfx/2d/canvas.h"

namespace gfx3d {
struct vec3d {
    double x, y, z;

    vec3d operator*(double x) const;
    vec3d operator-(vec3d const& other) const;
    vec3d operator-() const;
    vec3d operator+(vec3d const& other) const;
    double dot(vec3d const& other) const;
    vec3d cross(vec3d const& other) const;
    vec3d unit() const;
    double magnitude() const;
};

struct vertex {
    vec3d pos;
    vec3d normal;
};

struct face {
    vertex a, b, c;

    vec3d normal() const;
    vec3d centroid() const;
};

class object {
public:
    object(std::vector<face> faces, double radius) 
        : faces_(std::move(faces))
        , radius_(radius) {}

    void render(gfx2d::canvas& canvas) const;
    void render_wireframe(gfx2d::canvas& canvas) const;
    void rotate_y(double alpha);

    std::vector<face> const& faces() const { return faces_; }

private:
    std::vector<face> faces_;
    double radius_;
};

object load_from_obj(std::string const& filename);
}