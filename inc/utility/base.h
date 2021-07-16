
#ifndef BASE_H
#define BASE_H


#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <QDebug>
#include <profiler.h>

#include <vector>
#include "string.h"
#include <math.h>
#include <ctime>
#include <math.h>
#include <chrono>
#include "iostream"
#include "stdio.h"



using std::string;
using std::vector;
using sf::Vector2;
using sf::Vector2f;
using sf::Vector2i;
using sf::Vector2u;
using sf::Color;

template <typename T>
using HashTable = std::unordered_map<T,T>;
/*
template<typename T> struct HashTable {
  typedef std::unordered_map<T,T> table;
};
*/
//const Vector2f globalScale(10,10);
class PixelEngine;

//class DisplayText;
class Pixel;
class PixelDisplay;
struct DisplayStats;

class GameObject;
class Collider;
class Controller;
class KeyController;
class DynamicCoordinator;

class Painter;
class SpritePainter;
class PixelPainter;
class TexturePainter;
class TextPainter;
struct VertexPath;
class VertexPathPainter;
class ColliderPainter;

namespace Property
{
    class Property;
};
class Sensor;

class Texture;
class AnimatedTexture;

class ObjectTree;
class GameObjectGroup;
class InteractiveGameObject;
class InteractiveGameObjectGroup;

class Event;
class LayerItem;
template<class T>
class GeneralRect;
class GameObjectEventHandler;
class Timer;
class UserEventHandler;


class ObjSignal;
class ObjSubscriberList;

class GroupSignal;
class GroupSubscriberList;

class ControllerSignal;
class ControllerSubscriberList;

class UserEventSignal;
class UserEventSubscriberList;

class PainterSignal;
class PainterSubscriberList;


enum RenderLayerIndex
{
    layer_1,
    layer_2,
    layer_3,
    vertexPaths,
    texts,
    __size
};
#endif // BASE_H
