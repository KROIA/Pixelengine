#include <QCoreApplication>

#include "pixelDisplay.h"
#include "painter.h"
#include "collider.h"
#include "controller.h"
#include "keyController.h"
#include "keyboard.h"
#include "gameobject.h"
#include "gameObjectGroup.h"

#include "pixelengine.h"

#include <windows.h>
#include <QDebug>
#include "timer.h"

#include "event.h"
#include "userEventHandler.h"


#include "player.h"
#include "wall.h"

using sf::Image;

void userTickLoop(double tickInterval,unsigned long long tick);
void userDisplayLoop(double frameInterval,unsigned long long tick);

GameObject *getimportedObject();

Color getRainbow(double phase);
GameObjectGroup makeBoarder(PixelEngine *engine);
GameObjectGroup *factory_terain(const unsigned int &blocksX,const unsigned int &blocksY,const Point &bottomLeftOrigin);


Timer timer;
Timer fadeTimer;
Timer dbgTimer;
bool toggle = false;
double rad = 0;

Timer fpsTimer;
double fpsUpdateTimeInterval = 0.1;
double FPS = 0;
double fpsCounter = 0;

Timer tpsTimer;
double tpsUpdateTimeInterval = 0.1;
double TPS = 0;
double tpsCounter = 0;

Timer moveTimer;

Player          *player;
GameObject      *obstacle1;
Wall            *wall1;
GameObject      *imported;
GameObjectGroup *objectGroup;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*for(int i=0; i<10; i++)
    {
        Vector vec(cos(i)*10,sin(i)*10);
        Vector vec2 = Vector::rotate_90(vec);
        qDebug() <<"x="<<vec.getX()<<"\ty="<<vec.getY()<<"\tr90 x="<<vec2.getX()<<"\ty="<<vec2.getY();
    }*/

    // Generate the engine
    unsigned int mapWidth = 300;
    PointU windowSize(1500,800);
    PixelEngine engine(PointU(mapWidth,double(mapWidth)*double(windowSize.getY())/double(windowSize.getX())),PointU(1500,800));
    engine.set_setting_checkEventInterval(1.0f/30.0f);
    engine.set_setting_gameTickInterval(1.0f/120.0f);
    engine.set_setting_displayInterval(1.0f/60.0f);

    // Player 2
    player = new Player();
    player->setColor(Color(0,255,0));
    player->setStartPos(Point(50,50));
    player->setKeyBinding(KEYBOARD_KEY_W, KEYBOARD_KEY_A,
                          KEYBOARD_KEY_S, KEYBOARD_KEY_D);
    player->buildPlayer();
    player->setHitboxVisibility(true);

    // Obstacle 1
    obstacle1   = new GameObject();
    Controller *o1_controller = new Controller();
    obstacle1->setPos(100,100);
    Collider   *o1_collider = new Collider();
    o1_collider->addHitbox({Rect(PixelEngine::random(-10,10),PixelEngine::random(-10,10),PixelEngine::random(1,10),PixelEngine::random(1,10)),
                            Rect(PixelEngine::random(-10,10),PixelEngine::random(-10,10),PixelEngine::random(1,10),PixelEngine::random(1,10)),
                            Rect(PixelEngine::random(-10,10),PixelEngine::random(-10,10),PixelEngine::random(1,10),PixelEngine::random(1,10))});
    obstacle1->setCollider(o1_collider);
    obstacle1->addController(o1_controller);
    obstacle1->setHitboxVisibility(true);


    // Wall
    wall1 = new Wall();
    wall1->setDimension(PointU(1,50));
    wall1->setPos(Point(10,10));
    wall1->setColor(Color(142,50,1));

    imported = getimportedObject();
    imported->setHitboxVisibility(false);

    // Background
    /*GameObject *background = new GameObject();
    Painter *backgroundPainter = new Painter();
    Collider *backGroundCollider = new Collider();
    PixelEngine::loadFromImage("textures\\Background.jpg",backGroundCollider,backgroundPainter,ImageOrigin::topLeftCorner);
    delete backGroundCollider;
    background->setPainter(backgroundPainter);
    engine.addGameObject(background);
*/

    // Generate Ground
    GameObjectGroup *terainGroup = factory_terain(engine.getMapSize().getX()/16,5,Point(0,engine.getMapSize().getY()));


    // Make Boarder
    GameObjectGroup *boarderGroup = new GameObjectGroup();
    *boarderGroup = makeBoarder(&engine);

    // Make Group of Objects for toggle Hitbox in loop below
    objectGroup = new GameObjectGroup();
    objectGroup->add(player);
   // objectGroup->add(obstacle1);
    objectGroup->add(wall1);
    objectGroup->add(imported);
    objectGroup->add(boarderGroup);

    // Engine
    engine.setUserTickLoop(userTickLoop);
    engine.setUserDisplayLoop(userDisplayLoop);

    engine.addGameObject(obstacle1);
    engine.addGroup(objectGroup);
    engine.addGroup(terainGroup);


    // Set Interactions
    engine.setCollisionMultiInteraction({player,imported},{player,imported});

    engine.setCollisionSingleInteraction({player,imported},{obstacle1});
    engine.setCollisionSingleInteraction({player,imported},boarderGroup);

    engine.setCollisionSingleInteraction({player,imported},terainGroup);
    // End Interactions

    // Set RenderLayer
   // engine.setRenderLayer_BOTTOM(background);
    engine.setRenderLayer_TOP(wall1);
    engine.setRenderLayer_TOP(terainGroup);

//-------------------------------


    Timer statsTimer;
    Timer deleteTimer;
    bool removed = false;

    while(1)
    {
        /*if(statsTimer.start(0.1))
        {
            qDebug() << "FPS: "<<FPS<<"\tTPS: "<<TPS
                     <<"\tCollisionChecks: "<<Rect::stats_collisionCheckCount<<"\tCollisions: "<<Rect::stats_collisionCount
                     <<"\tC_Time: "<<engine.get_stats_checkCollisionTime() << " ms";
        }*/

        /*if(deleteTimer.start(5) && !removed)
        {
            qDebug() << "delete obstacle1";
            engine.deleteGameObject(obstacle1);
            //engine.removeGameObject(obstacle1);
            removed = true;
        }*/

        engine.checkEvent();
        engine.tick();
        engine.display();
        if(engine.get_setting_displayInterval()  > 0.002 &&
           engine.get_setting_gameTickInterval() > 0.002 &&
           engine.get_setting_eventHandleInterval() > 0.002)
        {
            Sleep(1);
        }
    }

    return a.exec();
}
void userTickLoop(double tickInterval,unsigned long long tick)
{
    Rect::stats_reset();
    if(tpsTimer.start(tpsUpdateTimeInterval))
    {
        TPS = tpsCounter / tpsUpdateTimeInterval;
        tpsCounter = 0;
    }
    tpsCounter++;

    //if(moveTimer.start(tickInterval))
    {
        imported->move(10*sin(double((tick*5)%360)*M_PI/180),
                       10*cos(double((tick*5)%360)*M_PI/180),Controller::MovingMode::override);
    }


}
void userDisplayLoop(double frameInterval,unsigned long long tick)
{
    if(fpsTimer.start(fpsUpdateTimeInterval))
    {
        FPS = fpsCounter / fpsUpdateTimeInterval;
        fpsCounter = 0;
    }
    fpsCounter++;
    if(timer.start(1)/* && !toggle*/)
    {
        //player->rotate_90(PointF(80,100));
        //player->rotate_90(PointF(player->getPos().getX(),player->getPos().getY()));
        //player->rotate_270();
        //player->setRotation(90);
        //qDebug() << "POS: "<<player->getPos().getX()<< "\t"<<player->getPos().getY();

        //imported->move(50,20);
        //objectGroup->setHitboxVisibility(true);
        //obstacle1->setHitboxVisibility(true);
        obstacle1->setPos(200,100);
        //objectGroup->rotate_90(PointF(50,50));
        toggle = !toggle;
    }
    if(fadeTimer.start(0.05))
    {
        player->setColor(getRainbow(rad));
        rad += M_PI/10;
        if(rad >= 2*M_PI)
            rad -= 2*M_PI;
    }
}

GameObject *getimportedObject()
{
    //Timer timer;
    //timer.start(1000);
    GameObject *obj         = new GameObject();
    Collider   *collider    = new Collider();
    Painter    *painter     = new Painter();
    KeyController *controller = new KeyController();

    controller->setKey_forMove_UP(KEYBOARD_KEY_W);
    controller->setKey_forMove_LEFT(KEYBOARD_KEY_A);
    controller->setKey_forMove_DOWN(KEYBOARD_KEY_S);
    controller->setKey_forMove_RIGHT(KEYBOARD_KEY_D);
    controller->setStepSize(1);

    Property::Property property = obj->getProperty();
    property.setBody_weight(1);
    property.setBody_material(Property::Material::Grass);
    property.setType_description(Property::Description::dynamicObstacle);
    obj->setProperty(property);
    obj->setPos(50,50);

    obj->setPainter(painter);
    obj->setCollider(collider);
    obj->addController(controller);
    PixelEngine::loadFromImage("textures\\Grass.png",collider,painter,ImageOrigin::bottomRightCorner);

    return obj;
}

Color getRainbow(double phase)
{
      int center = 128;
      int width = 127;
      double frequency = M_PI*2;
      Color color;
      color.r   = sin(frequency+2+phase) * width + center;
      color.g   = sin(frequency+0+phase) * width + center;
      color.b   = sin(frequency+4+phase) * width + center;
      return color;
}

GameObjectGroup makeBoarder(PixelEngine *engine)
{
    PointU mapSize = engine->getMapSize();
    unsigned int boarderSize = 3;
    Color color(142,50,1);

    Wall *wall_1 = new Wall();
    wall_1->setDimension(PointU(boarderSize,mapSize.getY()+2*boarderSize));
    wall_1->setPos(Point(-boarderSize,-boarderSize));
    wall_1->setColor(color);

    Wall *wall_2 = new Wall();
    wall_2->setDimension(PointU(boarderSize,mapSize.getY()+2*boarderSize));
    wall_2->setPos(Point(mapSize.getX(),-boarderSize));
    wall_2->setColor(color);

    Wall *wall_3 = new Wall();
    wall_3->setDimension(PointU(mapSize.getX(),boarderSize));
    wall_3->setPos(Point(0,-boarderSize));
    wall_3->setColor(color);

    Wall *wall_4 = new Wall();
    wall_4->setDimension(PointU(mapSize.getX(),boarderSize));
    wall_4->setPos(Point(0,mapSize.getY()));
    wall_4->setColor(color);

    GameObjectGroup group;
    group.add(wall_1);
    group.add(wall_2);
    group.add(wall_3);
    group.add(wall_4);
    engine->addGameObject(&group);
    return group;
}
GameObjectGroup *factory_terain(const unsigned int &blocksX,const unsigned int &blocksY,const Point &bottomLeftOrigin)
{
    GameObject *grassBlock = new GameObject();
    Collider *collider = new Collider();
    Painter  *painter = new Painter();
    Controller *controller = new Controller();
    if(!PixelEngine::loadFromImage("textures\\minecraft\\textures\\block\\grass_block_side.png",
                                   collider,painter,ImageOrigin::bottomLeftCorner))
        qDebug() << "can't load image";
    grassBlock->setCollider(collider);
    grassBlock->setPainter(painter);
    grassBlock->addController(controller);
    grassBlock->setPos(bottomLeftOrigin);

    Property::Property property = grassBlock->getProperty();
    property.setBody_weight(1);
    property.setBody_material(Property::Material::Grass);
    property.setType_description(Property::Description::staticObstacle);
    grassBlock->setProperty(property);


    Point blockSize(16,16);
    GameObjectGroup *group = new GameObjectGroup();
    for(size_t x=0; x<blocksX; x++)
    {
        for(size_t y=0; y<blocksY; y++)
        {
            GameObject *newBlock = new GameObject(*grassBlock);
            newBlock->setPos(bottomLeftOrigin.getX()+blockSize.getX()*x,bottomLeftOrigin.getY()-blockSize.getY()*y);
            group->add(newBlock);
            if(rand() % 5 == 0)
                y = blocksY;
        }
    }
    return group;
}
