#include "object.h"

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>

#include "gfx/2d/shapes.h"

namespace gfx3d {
namespace {
void rotate_y(vec3d& p, double alpha) {
    p.x = cos(alpha) * p.x + sin(alpha) * p.z;
    p.z = cos(alpha) * p.z - sin(alpha) * p.x;
}
}

vec3d vec3d::operator+(vec3d const& other) const {
    return {x+other.x, y+other.y, z+other.z};
}

vec3d vec3d::operator-(vec3d const& other) const {
    return {x-other.x, y-other.y, z-other.z};
}

vec3d vec3d::operator-() const {
    return {-x, -y, -z};
}

vec3d vec3d::operator*(double k) const {
    return {k*x, k*y, k*z};
}

double vec3d::dot(vec3d const& other) const {
    return x * other.x + y * other.y + z * other.z;
}

vec3d vec3d::cross(vec3d const& other) const {
    return {
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    };
}

double vec3d::magnitude() const {
    return std::sqrt(x*x + y*y + z*z);
}

vec3d vec3d::unit() const {
    double const m = magnitude();
    return {x/m, y/m, z/m};
}

vec3d face::normal() const {
    return (a.normal + b.normal + c.normal).unit();
    // return centroid().unit();
    // return ((c-a).cross(b-a).unit());
}

vec3d face::centroid() const {
    return (a.pos + b.pos + c.pos)*(1.0/3);
}

void object::render(gfx2d::canvas& canvas) const {
    auto scale = 0.75 * std::min(canvas.width(), canvas.height()) / 2.0 / radius_;
    vec3d const light{5, 5, 0};
    for (auto const& face : faces_) {
        auto const normal = face.normal();
        if (normal.z > 0) continue;
        int c = std::max(0.0, 255 * normal.dot((light - face.centroid()).unit()));
        gfx2d::color color{static_cast<uint8_t>(c), 0, 0};
        gfx2d::shapes::triangle_fill(canvas, 
            {static_cast<int>(face.a.pos.x * scale + canvas.width()/2), static_cast<int>(-face.a.pos.y * scale + canvas.height()/2)},
            {static_cast<int>(face.b.pos.x * scale + canvas.width()/2), static_cast<int>(-face.b.pos.y * scale + canvas.height()/2)},
            {static_cast<int>(face.c.pos.x * scale + canvas.width()/2), static_cast<int>(-face.c.pos.y * scale + canvas.height()/2)},
        color);
    }
}

void object::render_wireframe(gfx2d::canvas& canvas) const {
    auto scale = 0.75 * std::min(canvas.width(), canvas.height()) / 2.0 / radius_;
    for (auto const& face : faces_) {
        gfx2d::shapes::polygon(canvas, {
            {static_cast<int>(face.a.pos.x * scale + canvas.width()/2), static_cast<int>(-face.a.pos.y * scale + canvas.height()/2)},
            {static_cast<int>(face.b.pos.x * scale + canvas.width()/2), static_cast<int>(-face.b.pos.y * scale + canvas.height()/2)},
            {static_cast<int>(face.c.pos.x * scale + canvas.width()/2), static_cast<int>(-face.c.pos.y * scale + canvas.height()/2)}
        }, gfx2d::colors::WHITE);
    }
}


void object::rotate_y(double alpha) {
    for (auto& face : faces_) {
        ::gfx3d::rotate_y(face.a.pos, alpha);
        ::gfx3d::rotate_y(face.a.normal, alpha);
        ::gfx3d::rotate_y(face.b.pos, alpha);
        ::gfx3d::rotate_y(face.b.normal, alpha);
        ::gfx3d::rotate_y(face.c.pos, alpha);
        ::gfx3d::rotate_y(face.c.normal, alpha);
    }
}

namespace {
std::tuple<int, int, int> load_face_vertex(std::string const& def) {
    auto const first_slash_ptr = std::strchr(def.c_str(), '/');
    if (first_slash_ptr == nullptr) {
        return {std::stoi(def), -1, -1};
    }
    auto s1 = std::string(def, 0, first_slash_ptr - def.c_str());
    auto const vertex_index = std::stoi(s1);

    auto const second_slash_ptr = std::strchr(first_slash_ptr + 1, '/');
    if (second_slash_ptr == nullptr) {
        return {vertex_index, std::atoi(first_slash_ptr + 1), -1};
    }
    auto const texture_index = [&] {
        if (second_slash_ptr - first_slash_ptr - 1 == 0) {
            return -1;
        } else {
            return std::stoi(std::string(first_slash_ptr + 1, second_slash_ptr - first_slash_ptr - 1));
        }
    }();
    auto const normal_index = std::atoi(second_slash_ptr + 1);

    return {vertex_index, texture_index, normal_index};
}
}

object load_from_obj(std::string const& filename) {
    std::fstream file(filename);
    std::vector<vec3d> vertices;
    vec3d furthest_vertex{0.0, 0.0, 0.0};
    std::vector<vec3d> normals;
    std::vector<face> faces;
    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string type;
        ss >> type;
        if (type == "v") {
            vec3d vertex;
            ss >> vertex.x >> vertex.y >> vertex.z;
            if (vertex.magnitude() > furthest_vertex.magnitude()) {
                furthest_vertex = vertex;
            }
            vertices.push_back(vertex);
        } else if (type == "vn") {
            vec3d normal;
            ss >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal.unit());
        } else if (type == "f") {
            std::string vertex_str;
            std::vector<vertex> face_vertices;
            while (ss >> vertex_str) {
                auto const [vertex_index, texture_index, normal_index] = load_face_vertex(vertex_str);
                if (vertex_index - 1 > vertices.size()) {
                    std::cerr << "No vertex with index " << vertex_index << "\n";
                    continue;
                }
                face_vertices.push_back({vertices[vertex_index - 1], normals[normal_index - 1]});
            }
            if (face_vertices.size() != 3) {
                std::cerr << "Unexpected number of face vertices: " << face_vertices.size() << "\n";
                continue;
            }
            faces.push_back({face_vertices[0], face_vertices[1], face_vertices[2]});
        } else if (type == "vt") {
            // ignore for now
        } else {
            std::cerr << "Unknown entry type: " << type << "\n";
        }
    }
    return object(std::move(faces), furthest_vertex.magnitude());
}
}