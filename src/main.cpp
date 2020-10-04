#include <QCoreApplication>

#include "pixelDisplay.h"
#include "painter.h"
#include "collider.h"
#include "controller.h"
#include "keyController.h"
#include "keyboard.h"
#include "gameobject.h"
#include "interactiveGroup.h"

#include "pixelengine.h"

#include <windows.h>
#include <QDebug>
#include "timer.h"

#include "event.h"
#include "eventhandler.h"


#include "player.h"

void makeVisibleObsticle(Collider &collider,Painter &painter);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);




    //PixelDisplay display(PointU(1500,1000),PointU(150,100));

    Collider collider1;
    collider1.addHitBox({Rect(-1,0,2,2)});
    Painter painter1;
    makeVisibleObsticle(collider1,painter1);
    /*KeyController controller1;
    controller1.setKey_forMove_UP(KEYBOARD_KEY_W);
    controller1.setKey_forMove_LEFT(KEYBOARD_KEY_A);
    controller1.setKey_forMove_DOWN(KEYBOARD_KEY_S);
    controller1.setKey_forMove_RIGHT(KEYBOARD_KEY_D);*/

    Collider collider2;
    collider2.addHitBox({Rect(rand()%20-10,rand()%20-10,1+rand()%20,1+rand()%20),
                         Rect(rand()%20-10,rand()%20-10,1+rand()%20,1+rand()%20),
                         Rect(rand()%20-10,rand()%20-10,1+rand()%20,1+rand()%20)});
    //collider2.addHitBox({Rect(-5,0,5,4),Rect(0,-10,1,1),Rect(10,10,2,2)});
    Painter painter2;
    makeVisibleObsticle(collider2,painter2);
    Controller controller2;
    controller2.setPosInitial(40,40);





    GameObject object;
    object.setCollider(&collider1);
    //object.setController(&controller1);
    object.setPainter(&painter1);
    InteractiveCollisionGroup groupPlayer;
    groupPlayer.add(&object);

    // Player
    Player player;
    player.setColor(Color(0,0,255));
    player.setStartPos(Point(20,0));
    player.setKeyBinding(KEYBOARD_KEY_W,
                         KEYBOARD_KEY_A,
                         KEYBOARD_KEY_S,
                         KEYBOARD_KEY_D);
    player.buildPlayer();
    groupPlayer.add(&player);
    //makeVisibleObsticle(*player.getCollider(),*player.getPainter());

    // Player 2
    Player player2;
    player2.setColor(Color(255,0,0));
    player2.setStartPos(Point(60,0));
    player2.setKeyBinding(KEYBOARD_KEY_I,
                          KEYBOARD_KEY_J,
                          KEYBOARD_KEY_K,
                          KEYBOARD_KEY_L);
    player2.buildPlayer();
    groupPlayer.add(&player2);
    makeVisibleObsticle(*player2.getCollider(),*player2.getPainter());

    GameObject obsticle;
    obsticle.setCollider(&collider2);
    obsticle.setPainter(&painter2);
    obsticle.setController(&controller2);
    InteractiveCollisionGroup groupObsticle;
    groupObsticle.add(&obsticle);

    groupPlayer.interactWith(&groupObsticle);
    groupPlayer.interactWith(&groupPlayer);

    PainterGroup painterGroup;
    painterGroup.add(&object);
    painterGroup.add(&player2);
    painterGroup.add(&player);
    PainterGroup painterGroup2;
    painterGroup2.add(&obsticle);
    painterGroup2.setVisibility(true);

    PixelEngine engine;
    engine.set_setting_gameTickInterval(0.02);
    engine.set_setting_displayInterval(0.02);

    engine.addGameObject(&object);
    engine.addGameObject(&obsticle);
    engine.addGameObject(&player);
    engine.addGameObject(&player2);
    engine.addGroup(groupPlayer);
    engine.addGroup(groupObsticle);
    engine.addGroup(painterGroup);
    engine.addGroup(painterGroup2);


/*    Collider collider;
    Collider collider2;

    collider.addHitBox(Rect(Point(-5,-5),Point(5,5)));
    collider.addHitBox(Rect(Point(-3,-3),Point(6,6)));
    collider.addHitBox(Rect(Point(5,1),Point(8,3)));

    collider2.addHitBox(Rect(Point(-3,-3),Point(6,6)));


    vector<Painter> painterList;
    Painter painter2;

    painter2.addPixel(Pixel(collider2.getHitBox(0).getCornerPoint_TL(),Color(255,0,0)));
    painter2.addPixel(Pixel(collider2.getHitBox(0).getCornerPoint_TR(),Color(255,0,0)));
    painter2.addPixel(Pixel(collider2.getHitBox(0).getCornerPoint_BL(),Color(255,0,0)));
    painter2.addPixel(Pixel(collider2.getHitBox(0).getCornerPoint_BR(),Color(255,0,0)));
    collider2.setPos(30,30);

    painter2.setPos(collider2.getPos());

    for(size_t i=0; i<collider.getHitBox().size(); i++)
    {
        painterList.push_back(Painter());
        Color color(100+rand()%155,100+rand()%155,100+rand()%155);

        painterList[i].addPixel(Pixel(collider.getHitBox(i).getCornerPoint_TL(),color));
        painterList[i].addPixel(Pixel(collider.getHitBox(i).getCornerPoint_TR(),color));
        painterList[i].addPixel(Pixel(collider.getHitBox(i).getCornerPoint_BL(),color));
        painterList[i].addPixel(Pixel(collider.getHitBox(i).getCornerPoint_BR(),color));
    }
    painterList.push_back(Painter());
    painterList[painterList.size()-1].addPixel(Pixel(collider.getPos(),Color(255,255,255)));

    painterList[painterList.size()-1].addPixel(Pixel(collider.getBoundingBox().getCornerPoint_TL(),Color(0,0,255)));
    painterList[painterList.size()-1].addPixel(Pixel(collider.getBoundingBox().getCornerPoint_TR(),Color(0,0,255)));
    painterList[painterList.size()-1].addPixel(Pixel(collider.getBoundingBox().getCornerPoint_BL(),Color(0,0,255)));
    painterList[painterList.size()-1].addPixel(Pixel(collider.getBoundingBox().getCornerPoint_BR(),Color(0,0,255)));
*/
    /*Painter xPainter;
    for(int x=0; x<20;x++)
    {
        if(x%2==0)
        {
            xPainter.addPixel(Pixel(Point(x,0),Color(255,255,255)));
        }
        if(x%5==0)
        {
            xPainter.addPixel(Pixel(Point(x,1),Color(255,255,255)));
        }
        if(x%10==0)
        {
            xPainter.addPixel(Pixel(Point(x,2),Color(255,255,255)));
        }
    }*/

    Timer timer;
    Timer dbgTimer;
    while(1)
    {
       /* if(dbgTimer.start(1))
        {
            if(time == 0)
                qDebug() << "timer: "<<time<<"\tfps: inf.";
            else
                qDebug() << "timer: "<<time<<"\tfps: "<<1/time;
        }*/
        if(timer.start(0.0))
        {
            //qDebug() << "tick";

            //POINT p;
            //if (GetCursorPos(&p))
            {
           //     qDebug()<<"mouse: x="<<p.x<<"\ty="<<p.y;
                //cursor position now in p.x and p.y
            }
            //Point DeltaPos((p.x-200)/25-controller.getX(),(p.y-150)/10-controller.getY());
            /*Point DeltaPos;
            int moveLength = 1;
            if( GetAsyncKeyState(KEYBOARD_KEY_W))
            {
                DeltaPos.moveY(-moveLength);
            }
            if( GetAsyncKeyState(KEYBOARD_KEY_S))
            {
                DeltaPos.moveY(moveLength);
            }

            if( GetAsyncKeyState(KEYBOARD_KEY_A))
            {
                DeltaPos.moveX(-moveLength);
            }

            if( GetAsyncKeyState(KEYBOARD_KEY_D))
            {
                DeltaPos.moveX(moveLength);
            }*/


            /*if(DeltaPos.getX() != 0 || DeltaPos.getY() != 0)
            {
                if(DeltaPos.getX() == -1 || DeltaPos.getY() == -1)
                {
                    qDebug() << "";
                }
                //qDebug() << "delta: "<<DeltaPos.getX()<<"\t"<<DeltaPos.getY();
                controller1.move(DeltaPos);
            }*/
            engine.tick();
            engine.display();
            /*for(unsigned int i=0; i<controller1.getNeededMovingSteps(); i++)
            {
                for(unsigned int dir=0; dir<2; dir++)
                {
                    object.move(dir==0?Point(1,0):Point(0,1));
                    obsticle.move(dir==0?Point(1,0):Point(0,1));
                    object.checkCollision({&obsticle});
                }


            }*/

            //qDebug() << "collider.pos(): "<<collider.getPos().getX()<<"\t"<<collider.getPos().getY();
            //painter1.setPos(controller1.getPos());
            //painter2.setPos(collider2.getPos());


           // xPainter.draw(display);
            //painter1.draw(display);
           // object.draw(display);
           // obsticle.draw(display);
            //painter2.draw(display);


          //  display.display();
          //  display.handleEvents();

        }
       // Sleep(10);

    }

    return a.exec();
}
void makeVisibleObsticle(Collider &collider,Painter &painter)
{
    for(size_t i=0; i<collider.getHitBox().size(); i++)
    {
        Color color(100+rand()%155,100+rand()%155,100+rand()%155);
        painter.addPixel(Pixel(collider.getHitBox(i).getCornerPoint_TL(),color));
        painter.addPixel(Pixel(collider.getHitBox(i).getCornerPoint_TR(),color));
        painter.addPixel(Pixel(collider.getHitBox(i).getCornerPoint_BL(),color));
        painter.addPixel(Pixel(collider.getHitBox(i).getCornerPoint_BR(),color));
    }
    Color color(0,0,255);
    painter.addPixel(Pixel(collider.getBoundingBox().getCornerPoint_TL(),color));
    painter.addPixel(Pixel(collider.getBoundingBox().getCornerPoint_TR(),color));
    painter.addPixel(Pixel(collider.getBoundingBox().getCornerPoint_BL(),color));
    painter.addPixel(Pixel(collider.getBoundingBox().getCornerPoint_BR(),color));
}
