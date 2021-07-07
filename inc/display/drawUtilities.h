#ifndef DRAWUTILITIES_H
#define DRAWUTILITIES_H

#include "base.h"

struct VertexPath
{
    sf::Vertex *line;
    std::size_t length;
    sf::PrimitiveType type;

    ~VertexPath()
    {
        delete this->line;
    }
    const VertexPath &operator=(const VertexPath &other)
    {
        this->length = other.length;
        this->type   = other.type;
        this->line   = new sf::Vertex[this->length];
        for(size_t i=0; i<this->length; i++)
        {
            this->line[i] = other.line[i];
        }
        return *this;
    }

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
