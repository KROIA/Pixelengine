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
#include "eventhandler.h"


#include "player.h"
#include "wall.h"

using sf::Image;

void userTickLoop(double tickInterval);
void userDisplayLoop(double frameInterval);

GameObject *getimportedObject();
Color getRainbow(double phase);
GameObjectGroup makeBoarder(PixelEngine *engine);


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

Player *player1;
Player *player2;
GameObject *obsticle1;
Wall *wall1;
GameObject *imported;
GameObjectGroup *objectGroup;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Generate the engine
    unsigned int mapWidth = 500;
    PointU windowSize(1500,800);
    PixelEngine engine(PointU(mapWidth,double(mapWidth)*double(windowSize.getY())/double(windowSize.getX())),PointU(1500,800));
    engine.set_setting_checkEventInterval(0.01);
    engine.set_setting_gameTickInterval(0.01);
    engine.set_setting_displayInterval(0.01);

    // Player 1
    player1 = new Player();
    player1->setColor(Color(0,0,255));
    player1->setStartPos(Point(50,50));
    player1->setKeyBinding(KEYBOARD_KEY_W, KEYBOARD_KEY_A,
                           KEYBOARD_KEY_S,  KEYBOARD_KEY_D);
    player1->setStepSize(1);
    player1->buildPlayer();

    // Player 2
    player2 = new Player();
    player2->setColor(Color(255,0,0));
    player2->setStartPos(Point(80,50));
    player2->setKeyBinding(KEYBOARD_KEY_I, KEYBOARD_KEY_J,
                           KEYBOARD_KEY_K, KEYBOARD_KEY_L);
    player2->buildPlayer();
    player2->setHitboxVisibility(true);

    // Obsticle 1
    obsticle1   = new GameObject();
    Controller *o1_controller = new Controller();
    o1_controller->setPosInitial(100,100);
    Collider   *o1_collider = new Collider();
    o1_collider->addHitBox({Rect(PixelEngine::random(-10,10),PixelEngine::random(-10,10),PixelEngine::random(1,10),PixelEngine::random(1,10)),
                            Rect(PixelEngine::random(-10,10),PixelEngine::random(-10,10),PixelEngine::random(1,10),PixelEngine::random(1,10)),
                            Rect(PixelEngine::random(-10,10),PixelEngine::random(-10,10),PixelEngine::random(1,10),PixelEngine::random(1,10))});
    obsticle1->setCollider(o1_collider);
    obsticle1->setController(o1_controller);
    obsticle1->setHitboxVisibility(true);

    // Wall
    wall1 = new Wall();
    wall1->setDimension(PointU(50,1));
    wall1->getController()->setPosInitial(Point(20,150));
    wall1->setColor(Color(142,50,1));

    imported = getimportedObject();

    // Make Boarder
    GameObjectGroup *boarderGroup = new GameObjectGroup();
    *boarderGroup = makeBoarder(&engine);

    // Make Group of Objects for toggle hitbox in loop below
    objectGroup = new GameObjectGroup();
    objectGroup->add(player1);
    objectGroup->add(player2);
    objectGroup->add(obsticle1);
    objectGroup->add(wall1);
    objectGroup->add(imported);
    objectGroup->add(boarderGroup);

    // Engine
    engine.setUserTickLoop(userTickLoop);
    engine.setUserDisplayLoop(userDisplayLoop);

    engine.addGroup(objectGroup);



    // Set Interactions
    engine.setCollisionMultiInteraction({player1,player2,imported},{player1,player2,imported});

    engine.setCollisionSingleInteraction({player1,player2,imported},{obsticle1,wall1});
    engine.setCollisionSingleInteraction({player1,player2,imported},boarderGroup);
    // End Interactions
//-------------------------------


    Timer statsTimer;
    Timer deleteTimer;
    bool removed = false;

    while(1)
    {
        if(statsTimer.start(0.1))
        {
            qDebug() << "FPS: "<<FPS<<"\tTPS: "<<TPS
                     <<"\tCollisionChecks: "<<Rect::stats_collisionCheckCount<<"\tCollisions: "<<Rect::stats_collisionCount
                     <<"\tC_Time: "<<engine.get_stats_checkCollisionTime();
        }

        if(deleteTimer.start(5) && !removed)
        {
            qDebug() << "delete obsticle1";
            engine.deleteGameObject(obsticle1);
            //engine.removeGameObject(obsticle1);
            removed = true;
        }

        engine.checkEvent();
        engine.tick();
        engine.display();
        if(engine.get_setting_displayInterval()  > 0.001 &&
           engine.get_setting_gameTickInterval() > 0.001)
        {
            Sleep(1);
        }
    }

    return a.exec();
}
void userTickLoop(double tickInterval)
{
    Rect::stats_reset();
    if(tpsTimer.start(tpsUpdateTimeInterval))
    {
        TPS = tpsCounter / tpsUpdateTimeInterval;
        tpsCounter = 0;
    }
    tpsCounter++;


}
void userDisplayLoop(double frameInterval)
{
    if(fpsTimer.start(fpsUpdateTimeInterval))
    {
        FPS = fpsCounter / fpsUpdateTimeInterval;
        fpsCounter = 0;
    }
    fpsCounter++;
    if(timer.start(1))
    {
        objectGroup->setHitboxVisibility(toggle);
        toggle = !toggle;
    }
    if(fadeTimer.start(0.05))
    {
        player1->setColor(getRainbow(rad));
        rad += M_PI/10;
        if(rad >= 2*M_PI)
            rad -= 2*M_PI;
    }
}

GameObject *getimportedObject()
{
    GameObject *obj         = new GameObject();
    Collider   *collider    = new Collider();
    Painter    *painter     = new Painter();
    KeyController *controller = new KeyController();

    controller->setKey_forMove_UP(KEYBOARD_KEY_T);
    controller->setKey_forMove_LEFT(KEYBOARD_KEY_F);
    controller->setKey_forMove_DOWN(KEYBOARD_KEY_G);
    controller->setKey_forMove_RIGHT(KEYBOARD_KEY_H);
    controller->setPosInitial(250,100);

    obj->setPainter(painter);
    obj->setCollider(collider);
    obj->setController(controller);
    qDebug() << "import image...";

    Image image;
    image.loadFromFile("textues\\Einhornpng.png");

    sf::Vector2u size = image.getSize();
    Point middleOffset(-signed(size.x)/2,-signed(size.y)/2);

    double progress = 0;
    double maxProgress = size.x * size.y;

    collider->reserve(size.x * size.y);
    painter->reserve(size.x * size.y);
    for(unsigned int x=0; x<size.x; x++)
    {
        qDebug() << "[\t"<<100.f*progress/maxProgress<<"\t]";
        for(unsigned int y=0; y<size.y; y++)
        {
            Color color = image.getPixel(x,y);

            //qDebug() << "Pixel at: x="<<x<<"\ty="<<y<<"\t: r="<<color.r<<"\tg="<<color.g<<"\t"<<color.b<<"\ta="<<color.a;
            if(color.a != 0 && !(color.r == 255 && color.g == 255 && color.b == 255))
            {
                collider->addHitBox(Rect(middleOffset.getX()+x,middleOffset.getY()+y,1,1));
                painter->addPixel(Pixel(Point(middleOffset.getX()+x,middleOffset.getY()+y),color));
            }
            progress += 1;
        }
    }
    qDebug() << "import image done";
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
    wall_1->setDimension(PointU(boarderSize,mapSize.getY()-2*boarderSize));
    wall_1->getController()->setPosInitial(Point(0,boarderSize));
    wall_1->setColor(color);

    Wall *wall_2 = new Wall();
    wall_2->setDimension(PointU(boarderSize,mapSize.getY()-2*boarderSize));
    wall_2->getController()->setPosInitial(Point(mapSize.getX()-boarderSize,boarderSize));
    wall_2->setColor(color);

    Wall *wall_3 = new Wall();
    wall_3->setDimension(PointU(mapSize.getX(),boarderSize));
    wall_3->getController()->setPosInitial(Point(0,0));
    wall_3->setColor(color);

    Wall *wall_4 = new Wall();
    wall_4->setDimension(PointU(mapSize.getX(),boarderSize));
    wall_4->getController()->setPosInitial(Point(0,mapSize.getY()-boarderSize));
    wall_4->setColor(color);

    GameObjectGroup group;
    group.add(wall_1);
    group.add(wall_2);
    group.add(wall_3);
    group.add(wall_4);
    engine->addGameObject(&group);
    return group;
}
