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

#include "level.h"

using sf::Image;


void printStats(const PixelEngine::Statistics &stats);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Timer statsTimer;

    setup_level();

    while(1)
    {
        engine->checkEvent();
        engine->tick();
        engine->display();
        if(engine->get_setting_displayInterval()  > 0.002 &&
           engine->get_setting_gameTickInterval() > 0.002 &&
           engine->get_setting_eventHandleInterval() > 0.002)
        {
            //Sleep(1);
            nanosleep((const struct timespec[]){{0, 500000L}}, NULL);
        }
        if(statsTimer.start(0.1))
            printStats(engine->get_statistics());
    }

    return a.exec();
}

void printStats(const PixelEngine::Statistics &stats)
{
    qDebug() << "  Stats: ";
    qDebug() << "framesPerSecond:      \t" << stats.framesPerSecond;
    qDebug() << "ticksPerSecond:       \t" << stats.ticksPerSecond;
    qDebug() << "collisionsPerTick:    \t" << stats.collisionsPerTick;
    qDebug() << "collisionChecksPerTick:\t"<< stats.collisionChecksPerTick;
    qDebug() << "objectsInEngine:      \t" << stats.objectsInEngine;
    qDebug() << "collisionCheckTime:   \t" << stats.collisionCheckTime;
    qDebug() << "gameObjectTickTime:   \t" << stats.gameObjectTickTime;
    qDebug() << "checkEventTime:       \t" << stats.checkEventTime;
    qDebug() << "tickTime:             \t" << stats.tickTime;
    qDebug() << "displayTime:          \t" << stats.displayTime;
    qDebug() << "checkUserEventTime:   \t" << stats.checkUserEventTime;
    qDebug() << "userTickTime:         \t" << stats.userTickTime;
    qDebug() << "userDisplayTime:      \t" << stats.userDisplayTime;

    qDebug() << "  Stats end ";
}
