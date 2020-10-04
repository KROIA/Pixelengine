QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

isEmpty(ENGINE_PATH) {
    message( 'ENGINE_PATH is empty. use default value.' )
    ENGINE_PATH = $$PWD/PixelEngine
} else {
    message( 'ENGINE_PATH is not empty.' )
    message( $${ENGINE_PATH} )
}

#SFML include
SFML_VERSION = "2.5.1"
SFML_PATH    = "$$ENGINE_PATH/extern/SFML-$$SFML_VERSION"
include($$SFML_PATH/SFML.pri)
#end SFML include

PixelEngine_incPath = $$ENGINE_PATH/inc
PixelEngine_srcPath = $$ENGINE_PATH/src

INCLUDEPATH += $$incPath \
               $$PixelEngine_incPath \
               $$PixelEngine_incPath/utility \
               $$PixelEngine_incPath/utility/gameObjectGroup \
               $$PixelEngine_incPath/gameobject \
               $$PixelEngine_incPath/gameobject/basic \
               $$PixelEngine_incPath/gameobject/collider \
               $$PixelEngine_incPath/gameobject/collider/basic \
               $$PixelEngine_incPath/gameobject/controller \
               $$PixelEngine_incPath/gameobject/controller/basic \
               $$PixelEngine_incPath/gameobject/painter \
               $$PixelEngine_incPath/gameobject/painter/basic \
               $$PixelEngine_incPath/display

SOURCES += \
        $$PixelEngine_srcPath/pixelengine.cpp \
        $$PixelEngine_srcPath/display/pixelDisplay.cpp \
        $$PixelEngine_srcPath/display/pixel.cpp \
        $$PixelEngine_srcPath/gameobject/collider/basic/collider.cpp \
        $$PixelEngine_srcPath/gameobject/painter/basic/painter.cpp \
        $$PixelEngine_srcPath/gameobject/controller/basic/controller.cpp \
        $$PixelEngine_srcPath/gameobject/basic/gameobject.cpp \
        $$PixelEngine_srcPath/utility/gameObjectGroup/interactiveCollisionGroup.cpp \
        $$PixelEngine_srcPath/utility/gameObjectGroup/painterGroup.cpp \
        $$PixelEngine_srcPath/utility/event.cpp \
        $$PixelEngine_srcPath/utility/eventhandler.cpp \
        $$PixelEngine_srcPath/utility/timer.cpp \
        $$PixelEngine_srcPath/utility/layeritem.cpp

HEADERS += \
        $$PixelEngine_incPath/pixelengine.h \
        $$PixelEngine_incPath/display/pixelDisplay.h \
        $$PixelEngine_incPath/display/pixel.h \
        $$PixelEngine_incPath/gameobject/collider/basic/collider.h \
        $$PixelEngine_incPath/gameobject/painter/basic/painter.h \
        $$PixelEngine_incPath/gameobject/controller/basic/controller.h \
        $$PixelEngine_incPath/gameobject/basic/gameobject.h \
        $$PixelEngine_incPath/utility/event.h \
        $$PixelEngine_incPath/utility/eventhandler.h \
        $$PixelEngine_incPath/utility/gameObjectGroup/group.h \
        $$PixelEngine_incPath/utility/gameObjectGroup/interactiveGroup.h \
        $$PixelEngine_incPath/utility/gameObjectGroup/interactiveCollisionGroup.h \
        $$PixelEngine_incPath/utility/gameObjectGroup/painterGroup.h \
        $$PixelEngine_incPath/utility/point.h \
        $$PixelEngine_incPath/utility/vector.h \
        $$PixelEngine_incPath/utility/timer.h \
        $$PixelEngine_incPath/utility/rect.h \
        $$PixelEngine_incPath/utility/keyboard.h \
        $$PixelEngine_incPath/utility/layeritem.h
