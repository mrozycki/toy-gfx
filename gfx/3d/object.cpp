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
void object::render(gfx2d::canvas& canvas) const {
    for (auto const& face : faces_) {
        gfx2d::shapes::polygon(canvas, {
            {static_cast<int>((face.a.x + 2) * 200), static_cast<int>((-face.a.y + 2) * 200)},
            {static_cast<int>((face.b.x + 2) * 200), static_cast<int>((-face.b.y + 2) * 200)},
            {static_cast<int>((face.c.x + 2) * 200), static_cast<int>((-face.c.y + 2) * 200)}});
    }
}

object load_from_obj(std::string const& filename) {
    std::fstream file(filename);
    std::vector<point> vertices;
    std::vector<face> faces;
    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string type;
        ss >> type;
        if (type == "v") {
            point vertex;
            ss >> vertex.x >> vertex.y >> vertex.z;
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
                    if (face_vertices.size() >= 3) {
                        auto i = face_vertices.size() - 1;
                        faces.push_back({face_vertices[i], face_vertices[i-1], face_vertices[i-2]});
                    }
                }
            }
        } else if (type == "vn") {
            // ignore for now
        } else {
            std::cerr << "Unknown entry type: " << type << "\n";
        }
    }
    return object(std::move(faces));
}
}