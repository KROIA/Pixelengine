#ifndef DRAWUTILITIES_H
#define DRAWUTILITIES_H

#include "SFML/Graphics.hpp"

struct VertexPath
{
    sf::Vertex *line;
    std::size_t length;
    sf::PrimitiveType type;
};

#endif // DRAWUTILITIES_H
