#ifndef LEVEL_H
#define LEVEL_H

#include "pixelengine.h"
#include "wall.h"
#include "player.h"

extern PixelEngine     *engine;

extern Player          *player;
extern GameObject      *obstacle1;
extern Wall            *wall1;
extern GameObject      *imported;
extern GameObjectGroup *objectGroup;


extern Timer statsTimer;
extern Timer timer;
extern Timer fadeTimer;
extern Timer dbgTimer;
extern bool toggle;
extern double rad;

extern Timer fpsTimer;
extern double fpsUpdateTimeInterval;
extern double FPS;
extern double fpsCounter;

extern Timer tpsTimer;
extern double tpsUpdateTimeInterval;
extern double TPS;
extern double tpsCounter;


extern Event *keyEvent_P;
extern Event *keyEvent_O;

// toggle Hitbox
extern Event *keyEvent_H;
extern GameObjectGroup hitboxObjectList;
extern bool hitboxIsVisible;

void userEventLoop(double tickInterval,unsigned long long tick);
void userTickLoop(double tickInterval,unsigned long long tick);
void userDisplayLoop(double frameInterval,unsigned long long tick);

GameObject *getimportedObject();

Color getRainbow(double phase);
GameObjectGroup makeBoarder(PixelEngine *engine);
GameObjectGroup *factory_terain(const unsigned int &blocksX,const unsigned int &blocksY,const Point &bottomLeftOrigin);


void setup_level();
void clear_level();

#endif // LEVEL_H
