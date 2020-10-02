#include <QCoreApplication>

#include "pixelDisplay.h"
#include "painter.h"
#include "collider.h"
#include "controller.h"
#include "keyboard.h"

#include <windows.h>
#include <QDebug>
#include "timer.h"

#include "event.h"

void makeVisibleObsticle(Collider &collider,Painter &painter);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    PixelDisplay display(PointU(1500,1000),PointU(150,100));

    Collider collider1;
    collider1.addHitBox({Rect(-5,-5,2,10),Rect(-4,-4,2,2),Rect(5,5,5,8)});
    Painter painter1;
    makeVisibleObsticle(collider1,painter1);

    Collider collider2;
    collider2.addHitBox({Rect(rand()%20-10,rand()%20-10,rand()%20,rand()%20),
                         Rect(rand()%20-10,rand()%20-10,rand()%20,rand()%20),
                         Rect(rand()%20-10,rand()%20-10,rand()%20,rand()%20)});
    Painter painter2;
    makeVisibleObsticle(collider2,painter2);
    collider2.setPos(40,40);

    Controller controller;
    //controller

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
    double time;
    bool moveDirX = true;
    while(1)
    {
       /* if(dbgTimer.start(1))
        {
            if(time == 0)
                qDebug() << "timer: "<<time<<"\tfps: inf.";
            else
                qDebug() << "timer: "<<time<<"\tfps: "<<1/time;
        }*/
        if(timer.start(0.01))
        {
            unsigned short iState = GetAsyncKeyState(0x41) ;
            POINT p;
            if (GetCursorPos(&p))
            {
           //     qDebug()<<"mouse: x="<<p.x<<"\ty="<<p.y;
                //cursor position now in p.x and p.y
            }
            //Point DeltaPos((p.x-200)/25-controller.getX(),(p.y-150)/10-controller.getY());
            Point DeltaPos;
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
            }


            if(DeltaPos.getX() != 0 || DeltaPos.getY() != 0)
            {
                if(DeltaPos.getX() == -1 || DeltaPos.getY() == -1)
                {
                    qDebug() << "";
                }
                qDebug() << "delta: "<<DeltaPos.getX()<<"\t"<<DeltaPos.getY();
                controller.move(DeltaPos);


                for(unsigned int i=0; i<controller.getNeededMovingSteps(); i++)
                {
                    for(unsigned int dir=0; dir<2; dir++)
                    {
                        controller.tick(dir==0?Point(1,0):Point(0,1));
                        collider1.setPos(controller.getPos());

                        if(collider1.intersectsBoundingBox(collider2))
                        {
                            if(collider1.collides(collider2))
                            {
                                controller.setToLastPos();
                            }
                        }
                    }
                }
               /* for(int i=0; i<2; i++)
                {


                    if(moveDirX)
                    {
                        int dirNegative = DeltaPos.getX() < 0? -1 : 1;
                       // qDebug() << "move X";
                        for(int x=0; x<DeltaPos.getX()*dirNegative; x++)
                        {
                          //  qDebug() << x;
                            collider1.setPos(collider1.getX()+dirNegative,collider1.getY());
                            if(collider1.intersectsBoundingBox(collider2))
                            {
                                if(collider1.collides(collider2))
                                {
                                    collider1.setToLastPos();
                                }
                            }
                        }
                    }
                    else
                    {
                        int dirNegative = DeltaPos.getY() < 0? -1 : 1;
                       // qDebug() << "move Y";
                        for(int y=0; y<DeltaPos.getY()*dirNegative; y++)
                        {
                            //qDebug() << x;
                            collider1.setPos(collider1.getX(),collider1.getY()+dirNegative);
                            if(collider1.intersectsBoundingBox(collider2))
                            {
                                if(collider1.collides(collider2))
                                {
                                    collider1.setToLastPos();
                                }
                            }
                        }
                    }

                    moveDirX = !moveDirX;


                }*/
            }

            //qDebug() << "collider.pos(): "<<collider.getPos().getX()<<"\t"<<collider.getPos().getY();
            painter1.setPos(controller.getPos());
            painter2.setPos(collider2.getPos());

           // xPainter.draw(display);
            painter1.draw(display);
            painter2.draw(display);


            display.display();
            display.handleEvents();

        }
        Sleep(10);

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
