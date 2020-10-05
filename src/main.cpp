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

Color getRainbow(double phase);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Player 1
    Player *player1 = new Player();
    player1->setColor(Color(0,0,255));
    player1->setStartPos(Point(20,0));
    player1->setKeyBinding(KEYBOARD_KEY_W, KEYBOARD_KEY_A,
                           KEYBOARD_KEY_S,  KEYBOARD_KEY_D);
    player1->buildPlayer();

    // Player 2
    Player *player2 = new Player();
    player2->setColor(Color(255,0,0));
    player2->setStartPos(Point(60,0));
    player2->setKeyBinding(KEYBOARD_KEY_I, KEYBOARD_KEY_J,
                           KEYBOARD_KEY_K, KEYBOARD_KEY_L);
    player2->buildPlayer();
    player2->setHitboxVisibility(true);

    // Obsticle 1
    GameObject *obsticle1   = new GameObject();
    Controller *o1_controller = new Controller();
    o1_controller->setPosInitial(40,30);
    Collider   *o1_collider = new Collider();
    o1_collider->addHitBox({Rect(PixelEngine::random(-10,10),PixelEngine::random(-10,10),PixelEngine::random(1,10),PixelEngine::random(1,10)),
                            Rect(PixelEngine::random(-10,10),PixelEngine::random(-10,10),PixelEngine::random(1,10),PixelEngine::random(1,10)),
                            Rect(PixelEngine::random(-10,10),PixelEngine::random(-10,10),PixelEngine::random(1,10),PixelEngine::random(1,10))});
    obsticle1->setCollider(o1_collider);
    obsticle1->setController(o1_controller);
    obsticle1->setHitboxVisibility(true);

    // Wall
    Wall *wall1 = new Wall();
    wall1->setDimension(PointU(50,1));
    wall1->getController()->setPosInitial(Point(20,95));
    wall1->setColor(Color(142,50,1));

    // Make Group of Objects for toggle hitbox in loop below
    GameObjectGroup objectGroup;
    objectGroup.push_back(player1);
    objectGroup.push_back(player2);
    objectGroup.push_back(obsticle1);
    objectGroup.push_back(wall1);

    // Set Interactions
    player1->addInteraction_collision_with(player2);
    player1->addInteraction_collision_with(obsticle1);
    player1->addInteraction_collision_with(wall1);

    player2->addInteraction_collision_with(player1);
    player2->addInteraction_collision_with(obsticle1);
    player2->addInteraction_collision_with(wall1);
    // End Interactions

    // Engine
    PixelEngine engine;
    engine.set_setting_gameTickInterval(0.02);
    engine.set_setting_displayInterval(0.02);
    engine.addGameObject(obsticle1);
    engine.addGameObject(player1);
    engine.addGameObject(player2);
    engine.addGameObject(wall1);
//-------------------------------

    Timer timer;
    Timer fadeTimer;
    Timer dbgTimer;
    bool toggle = false;
    Color colorFade(0,0,0);
    double rad = 0;


    while(1)
    {
        if(timer.start(1))
        {
            objectGroup.setHitboxVisibility(toggle);
            toggle = !toggle;
        }
        if(fadeTimer.start(0.05))
        {
            player1->setColor(getRainbow(rad));
            rad += M_PI/10;
            if(rad >= 2*M_PI)
                rad -= 2*M_PI;
        }

        engine.tick();
        engine.display();
    }

    return a.exec();
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
