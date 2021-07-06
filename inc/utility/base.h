
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


//const Vector2f globalScale(10,10);

class DisplayText;
class Pixel;
class PixelDisplay;

class GameObject;
class Collider;
class Controller;
class KeyController;
class DynamicCoordinator;

class Painter;
class PixelPainter;
class TexturePainter;
namespace Property
{
    class Property;
};
class Sensor;

class Texture;
class AnimatedTexture;

class GameObjectGroup;
class InteractiveGameObject;
class InteractiveGameObjectGroup;
class ManagedGameObjectGroup;

struct ChunkID;
class Chunk;
class ChunkMap;

class Event;
class LayerItem;
template<class T>
class GeneralRect;
class GameObjectEventHandler;
class Timer;
class UserEventHandler;

//template<class T>
class ObjSignal;
class ObjSubscriberList;

class GroupSignal;
class GroupSubscriberList;

class ChunkSignal;
class ChunkSubscriberList;
#endif // BASE_H
