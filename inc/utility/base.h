
#ifndef BASE_H
#define BASE_H
#if defined __has_include
#  if __has_include (<pixelEngineSettings.h>)
#    include <pixelEngineSettings.h>
#    pragma message( "Applying Profiler settings from  pixelEngineSettings.h " )
#  else
// Timing
//#define PIXELENGINE_NO_TIMED_LOOPS

// Performance
#define PIXELENGINE_USE_THREADS

// Physics
#define PIXELENGINE_ENABLE_COLLISION
#define PIXELENGINE_ENABLE_GAME_OBJECT_EVENTS

//  Debuging
#define PIXELENGINE_STATISTICS
//#define PIXELENGINE_DBUG_THREAD

#ifdef BUILD_WITH_EASY_PROFILER
    #define PIXELENGINE_NO_TIMED_LOOPS
#endif
#pragma message( "Applying PixelEngine settings from " __FILE__ )
#  endif
#endif


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

class Painter;
class SpritePainter;
class PixelPainter;
class TexturePainter;
class TextPainter;
struct VertexPath;
class VertexPathPainter;
class ColliderPainter;

//class DisplayText;
class Pixel;
//class GameObjectDisplayInterface;
class PixelDisplay;

struct DisplayStats
{
    unsigned long long renderSprites;
    unsigned long long renderVertexPaths;
    unsigned long long renderText;
    unsigned long long activePainters;
    vector<unsigned long long> avtivePaintersInLayer;
};

//class GameObjectEngine_Interface;
class Submodule;
class GameObject;
class Collider;
class Controller;
class KeyController;
class DynamicCoordinator;



namespace Property
{
    class Property;
};
class Sensor;
class RectSensor;

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
class EngineInterface;
class Timer;
class UserEventHandler;


class SubmoduleSignal;
class SubmoduleSubscriberList;

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
