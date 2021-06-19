#include "object.h"

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "gfx/2d/shapes.h"

namespace gfx3d {
namespace {
void rotate_y(point& p, double alpha) {
    p.x = cos(alpha) * p.x + sin(alpha) * p.z;
    p.z = cos(alpha) * p.z - sin(alpha) * p.x;
}
}

void object::render(gfx2d::canvas& canvas) const {
    double scale = 0.75 * std::min(canvas.width(), canvas.height()) / 2.0 / radius_;
    for (auto const& face : faces_) {
        gfx2d::shapes::triangle_fill(canvas, 
            {static_cast<int>(face.a.x * scale + canvas.width()/2), static_cast<int>(-face.a.y * scale + canvas.height()/2)},
            {static_cast<int>(face.b.x * scale + canvas.width()/2), static_cast<int>(-face.b.y * scale + canvas.height()/2)},
            {static_cast<int>(face.c.x * scale + canvas.width()/2), static_cast<int>(-face.c.y * scale + canvas.height()/2)},
        gfx2d::colors::RED);
    }
}

void object::rotate_y(double alpha) {
    for (auto& face : faces_) {
        ::gfx3d::rotate_y(face.a, alpha);
        ::gfx3d::rotate_y(face.b, alpha);
        ::gfx3d::rotate_y(face.c, alpha);
    }
}

object load_from_obj(std::string const& filename) {
    std::fstream file(filename);
    std::vector<point> vertices;
    point furthest_point{0.0, 0.0, 0.0};
    std::vector<face> faces;
    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string type;
        ss >> type;
        if (type == "v") {
            point vertex;
            ss >> vertex.x >> vertex.y >> vertex.z;
            if (vertex.distance() > furthest_point.distance()) {
                furthest_point = vertex;
            }
            vertices.push_back(vertex);
        } else if (type == "f") {
            std::string vertex;
            std::vector<point> face_vertices;
            while (ss >> vertex) {
                auto slash_index = strchr(vertex.c_str(), '/') - vertex.c_str();
                auto vertex_index = atoi(std::string(vertex, 0, slash_index).c_str());
                if (vertex_index < 1 || vertex_index > vertices.size()) {
                    std::cerr << "Vertex out of bounds: " << vertex_index << "\n";
                } else {
                    face_vertices.push_back(vertices[vertex_index - 1]);
                }
            }
            if (face_vertices.size() != 3) {
                std::cerr << "Unexpected number of face vertices: " << face_vertices.size() << "\n";
                continue;
            }
            faces.push_back({face_vertices[0], face_vertices[1], face_vertices[2]});
        } else if (type == "vn" || type == "vt") {
            // ignore for now
        } else {
            std::cerr << "Unknown entry type: " << type << "\n";
        }
    }
    return object(std::move(faces), furthest_point.distance());
}
}