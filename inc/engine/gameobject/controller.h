#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "layeritem.h"
#include "SFML/System.hpp"
#include "vector"
#include "point.h"

using std::vector;

class Controller    :   public LayerItem
{
    public:
        Controller();
        Controller(const Controller &other);
        virtual  ~Controller();



    protected:

    private:
};
#endif
