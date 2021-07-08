# Pixelengine
 
 A simple game engine
 
 This Project uses SFML and EasyProfiler

## SFML info
--------------
This Engine uses [SFML 2.5.1](https://github.com/SFML/SFML)<br>
You have to install the MinGW 7.3.0 64bit compiler and CMake.<br>
<br>
The SFML repository is automatically downloaded when the repository is cloned. <br>
The SFML repo can be found under: PixelEngine/extern/SFML and must be built first.<br>
Build the debug and release Version.<br>
Make sure the SFML build directory looks like this:<br>
DEBUG: **extern/SFML/bin/Debug/lib**<br>
RELEASE: **extern/SFML/bin/Release/lib**<br>
<br>

If you're using QT, you don't have to copy the SFML-dll's from the SFML bin path.<br>
Otherweise, you find them under:<br>
DEBUG: **extern/SFML/bin/Debug/lib/xy.dll**<br>
RELEASE: **extern/SFML/bin/Release/lib/xy.dll**<br>

Easy profiler info
--------------
The [easy profiler](https://github.com/yse/easy_profiler) is used to capture the runtimeperformance of the engine.<br>
If you want to use the Profiler, compile it using the: Pixelengine/extern/easy_profiler/CMakeLists.txt<br>
Make sure the SFML build directory looks like this:<br>
DEBUG: **extern/easy_profiler/bin/Debug/lib**<br>
RELEASE: **extern/easy_profiler/bin/Release/lib**<br>
<br>
The profiler will generate a profiler.prof file inyour build path after executing your code. <br>
This file can be open with the built application: Pixelengine/extern/easy_profiler/bin/Release/bin/profiler_gui.exe
The profiler is normaly deactivated but can be activated by defining "BUILD_WITH_EASY_PROFILER" in your .pro file: <br>
```c++
CONFIG += BUILD_WITH_EASY_PROFILER
```
You also can add this define to the buildconfiguration.
This is my favorite, because this activates the Profiler automatically when you change the build to "Profile".
<img src="https://github.com/KROIA/Pixelengine/blob/master/images/EasyProfilerSetting.PNG" width="800">

## Engine usage
--------------

Include the Pixelengine in to your Project by editing your .pro file:
```c++
file: .pro
...
include($$PWD/extern/PixelEngine/PixelEngine.pri)
...
```
$$PWD is your current project 

### Basic code
```c++
#include "pixelengine.h"

// Declare the engine
PixelEngine *myEngine;

int main(int argc, char *argv[])
{
    Vector2u mapSize(100,100);                       // The mapsize in Pixels (not important for now)
    Vector2u windowSize(1000,1000);                  // The windowsize in pixels
    myEngine = new PixelEngine(mapSize, windowSize); // create the engine

   // If you close the window by klicking the X, this loop gets interrupted.
    while(myEngine->running())                       
    {
        // Weill update the engine
        myEngine->loop();
        // Alternative you can call:
        /*
        myEngine->checkEvent();
        myEngine->tick();
        myEngine->display();
        */
    }

    // Cleanup and exit
    delete myEngine;
    return 0;
}
```
This will create a running empty engine. Now we want to add content to it.
Every element in the engine will a GameObject *.
### Create a simple player
```c++
GameObject *buildPlayer(int up, int left, int down, int right)
{
    // Create a simple gameObject
    GameObject     *player      = new GameObject();

    // A GameObject can have a texture which will be put on the painter.
    Texture        *texture     = new Texture();
    // The painter will be put on the GameObject
    TexturePainter *painter     = new TexturePainter();
    // The controller will move the GameObject. You can add multiple Controller
    KeyController  *controller  = new KeyController();

    // Load the texture
    texture->loadTexture("myPlayer.png");
    painter->setTexture(texture);

    // Setup the keyBinding for the controller
    controller->setKey_forMove_DOWN(down);
    controller->setKey_forMove_UP(up);
    controller->setKey_forMove_LEFT(left);
    controller->setKey_forMove_RIGHT(right);
    // Set the stepsize for each buttonpress to 1 Pixel/Tick
    controller->setStepSize(1);

    // Set the painter and controller to the object
    player->setPainter(painter);
    player->addController(controller);

    return player;
}
```
We created a function which will generate a player object.
We implement this in the main().
```c++
    ...
    myEngine = new PixelEngine(mapSize, windowSize); // create the engine

    // Generate my player
    GameObject *playerObj = buildPlayer(KEYBOARD_KEY_W,KEYBOARD_KEY_A,KEYBOARD_KEY_S,KEYBOARD_KEY_D);
    playerObj->setPos(50,50);

    // Add the object to the engine
    myEngine->addGameObject(playerObj);

    // Prepare all objects in the engine
    myEngine->setup();

   // If you close the window by klicking the X, this loop gets interrupted.
    while(myEngine->running())
    ...
```
If you run the application, you will find your Playertexture on the screen.
Move it with the keys: W,A,S,D.
<img src="https://github.com/KROIA/Pixelengine/blob/master/images/example/Player_simple.PNG" width="400"><br>
Let's add a second player:
```C++
    // Generate my player
    GameObject *playerObj = buildPlayer(KEYBOARD_KEY_W,KEYBOARD_KEY_A,KEYBOARD_KEY_S,KEYBOARD_KEY_D);
    playerObj->setPos(25,50);
    GameObject *otherPlayer = buildPlayer(KEYBOARD_KEY_I,KEYBOARD_KEY_J,KEYBOARD_KEY_K,KEYBOARD_KEY_L);
    otherPlayer->setPos(75,50);

    // Add the object to the engine
    myEngine->addGameObject(playerObj);
    myEngine->addGameObject(otherPlayer);

    // Prepare all objects in the engine
    myEngine->setup();
```
Now we have two player, but they can't interact with each other.
Lets give them a hitbox:
in: GameObject *buildPlayer(...):
```C++
    // The collider will handle the collision detection with the objects
    Collider       *collider    = new Collider();
    // Setup the Hitboxes
    //   This will generate the Hitboxes based on the pixels of the texture
    collider->setHitboxFromTexture(texture);
    //   You also can define your own hitboxes. You can add as many as you want.
    collider->addHitbox(RectF(5,0,5,1));
    
    player->setCollider(collider);

    // For debuging you can use this functions:
    player->setVisibility_collider_hitbox(true);
    // The BoundingBox is the rectangle which includes all hitboxes
    player->setVisibility_collider_boundingBox(true);
...
```
in the main(...):
```C++
...
    // Prepare all objects in the engine
    myEngine->setup();
    // Set collision interaction between both objects
    myEngine->setCollisionMultiInteraction(playerObj,otherPlayer);

   // If you close the window by klicking the X, this loop gets interrupted.
    while(myEngine->running())
...
```
<img src="https://github.com/KROIA/Pixelengine/blob/master/images/example/PlayersWithCollider.PNG" width="800"><br>
That is the basic usage for this engine, if you want to create more adwanced GameObjects, crate a class which inherits from GameObject.
```C++
    class MySpecialObject   :   public GameObject
    {
        public:
            MySpecialObject(){};

    };

    // main loop:
   ...
    MySpecialObject *obj = new MySpecialObject();

    // Add the object to the engine
    myEngine->addGameObject(obj);
   ...
```

