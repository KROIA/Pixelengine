#ifndef LEVEL_H
#define LEVEL_H

#include "pixelengine.h"
#include "wall.h"
#include "player.h"
#include "texture.h"
#include "animatedTexture.h"

extern PixelEngine     *engine;

extern Player          *player;
extern GameObject      *obstacle1;
extern Wall            *wall1;
extern GameObject      *imported;
extern ManagedGameObjectGroup *objectGroup;
extern AnimatedTexture *animatedTexture;
extern GameObject      *waterBlock;
extern AnimatedTexture *waterTexture;
extern vector<AnimatedTexture *>waterTextureList;


extern Timer statsTimer;
extern Timer timer;
extern Timer timer2;
extern Timer fadeTimer;
extern Timer dbgTimer;
extern bool toggle;
extern double rad;


extern Event *keyEvent_P;
extern Event *keyEvent_O;

// toggle Hitbox
extern Event *keyEvent_H;
extern ManagedGameObjectGroup hitboxObjectList;
extern bool hitboxIsVisible;

void userEventLoop(double tickInterval,unsigned long long tick);
void userTickLoop(double tickInterval,unsigned long long tick);
void userDisplayLoop(double frameInterval,unsigned long long tick);

GameObject *getimportedObject();

Color getRainbow(double phase);
ManagedGameObjectGroup *makeBoarder(PixelEngine *engine);
ManagedGameObjectGroup *factory_terain(const unsigned int &blocksX,const unsigned int &blocksY,const Point &bottomLeftOrigin);


void setup_level();
void clear_level();

#endif // LEVEL_H
