#ifndef DRAWUTILITIES_H
#define DRAWUTILITIES_H

#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"

struct VertexPath
{
    sf::Vertex *line;
    std::size_t length;
    sf::PrimitiveType type;

    void move(sf::Vector2f vec)
    {
        for(size_t i=0; i<length; i++)
        {
            line[i].position += vec;
        }
    }
};

//inline VertexPath getCrossedRect()

#endif // DRAWUTILITIES_H
