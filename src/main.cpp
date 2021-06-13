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




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Timer statsTimer;
    Timer deleteTimer;

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
            Sleep(1);
        }
    }

    return a.exec();
}

