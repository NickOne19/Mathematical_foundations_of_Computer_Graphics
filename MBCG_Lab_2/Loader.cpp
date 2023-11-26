#include <iostream>
#include "Loader.h"
#include <fstream>
#include <sstream>

Loader::Loader(const std::string& path) :
    m_path(path)
{
    Read2DModel();
}

Loader::~Loader()
{
    std::cout << "\nModel destroyed";
}

std::vector<Vector2D> Loader::vertices() const
{
    return m_vertices;
}

std::vector<int> Loader::indices() const
{
    return m_indices;
}

void Loader::Read2DModel() {
    m_vertices.clear();
    m_indices.clear();

    std::ifstream file(m_path);
    if (!file) {
        throw std::runtime_error("Failed to open the file: " + m_path);
    }

    std::string line;
    int lineNum = 0;

    while (std::getline(file, line)) {
        lineNum++;

        std::istringstream iss(line);
        std::string keyword;
        iss >> keyword;

        if (keyword == "v") {
            double x, y;
            if (iss >> x >> y) {
                m_vertices.push_back(Vector2D(x, y));
            }
            else {
                throw std::runtime_error("Error parsing vertex on line " + std::to_string(lineNum));
            }
        }
        else if (keyword == "f") {
            int index;
            while (iss >> index) {
                m_indices.push_back(index);
            }
        }
    }

    if (file.bad()) {
        throw std::runtime_error("Error reading the file: " + m_path);
    }
}

bool Loader::isLoad()
{
    return !m_vertices.empty() && !m_indices.empty();
}

void Loader::printVertices() const {
    std::cout << "Vertices:" << std::endl;
    for (const Vector2D& vertex : m_vertices) {
        std::cout << "v " << vertex.x() << " " << vertex.y() << std::endl;
    }
}

void Loader::printIndices() const {
    std::cout << "Indices:" << std::endl;
    for (int index : m_indices) {
        std::cout << "f " << index << std::endl;
    }
}