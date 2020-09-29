#include <QCoreApplication>

#include "pixelDisplay.h"
#include "painter.h"
#include "collider.h"

#include <windows.h>
#include <QDebug>
#include "timer.h"

#include "event.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    PixelDisplay display(PointU(1000,1000),PointU(50,50));

    Collider collider;

    collider.addHitBox(Rect(Point(-5,-5),Point(5,5)));
    collider.addHitBox(Rect(Point(-3,-3),Point(6,6)));
    collider.addHitBox(Rect(Point(5,1),Point(8,3)));

    vector<Painter> painterList;

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



    Timer timer;
    Timer dbgTimer;
    double time;
    while(1)
    {
        timer.update();
        time = time*0.5+0.5*timer.getTime();
        timer.stop();
        timer.start(1000);
        if(dbgTimer.start(1))
        {
            if(time == 0)
                qDebug() << "timer: "<<time<<"\tfps: inf.";
            else
                qDebug() << "timer: "<<time<<"\tfps: "<<1/time;
        }
        unsigned short iState = GetAsyncKeyState(0x41) ;
        //qDebug() << iState;
        POINT p;
        if (GetCursorPos(&p))
        {
       //     qDebug()<<"mouse: x="<<p.x<<"\ty="<<p.y;
            //cursor position now in p.x and p.y
        }
        Sleep(50);



        collider.setPos(p.x/50,p.y/50);
        for(size_t i=0; i<painterList.size(); i++)
        {
            painterList[i].setPos(collider.getPos());
            painterList[i].draw(display);
        }


        display.display();

    }

    return a.exec();
}
