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
    #message( 'ENGINE_PATH is empty. use default value.' )
    ENGINE_PATH = $$PWD
} else {
    #message( 'ENGINE_PATH is not empty.' )
    #message( $${ENGINE_PATH} )
}

message( "----- PixelEngine.pri ------- " )
message( "  Path: $$ENGINE_PATH " )




include(extern/easy_profiler.pri)
include(extern/SFML.pri)

PixelEngine_incPath = $$ENGINE_PATH/inc
PixelEngine_srcPath = $$ENGINE_PATH/src

INCLUDEPATH += $$incPath \
               $$PixelEngine_incPath \
               $$PixelEngine_incPath/utility \
               $$PixelEngine_incPath/utility/group \
               $$PixelEngine_incPath/utility/group/chunk \
               $$PixelEngine_incPath/gameobject \
               $$PixelEngine_incPath/gameobject/basic \
               $$PixelEngine_incPath/gameobject/collider \
               $$PixelEngine_incPath/gameobject/collider/basic \
               $$PixelEngine_incPath/gameobject/controller \
               $$PixelEngine_incPath/gameobject/controller/basic \
               $$PixelEngine_incPath/gameobject/painter \
               $$PixelEngine_incPath/gameobject/painter/basic \
               $$PixelEngine_incPath/gameobject/property/ \
               $$PixelEngine_incPath/gameobject/sensor \
               $$PixelEngine_incPath/gameobject/sensor/basic \
               $$PixelEngine_incPath/gameobject/texture \
               $$PixelEngine_incPath/display

SOURCES += \
        $$PixelEngine_srcPath/gameobject/painter/colliderPainter.cpp \
        $$PixelEngine_srcPath/gameobject/painter/textPainter.cpp \
        $$PixelEngine_srcPath/gameobject/painter/vertexPathPainter.cpp \
        $$PixelEngine_srcPath/utility/group/objectTree.cpp \
        $$PixelEngine_srcPath/utility/signalSubscriber.cpp \
        $$PixelEngine_srcPath/utility/settings.cpp \
        $$PixelEngine_srcPath/display/drawUtilities.cpp \
        $$PixelEngine_srcPath/gameobject/painter/texturePainter.cpp \
        $$PixelEngine_srcPath/utility/group/InteractiveGameObject.cpp \
        $$PixelEngine_srcPath/utility/group/InteractiveGameObjectGroup.cpp \
        $$PixelEngine_srcPath/gameobject/controller/basic/dynamicCoordinator.cpp \
        $$PixelEngine_srcPath/gameobject/painter/pixelpainter.cpp \
        $$PixelEngine_srcPath/pixelengine.cpp \
        $$PixelEngine_srcPath/display/pixelDisplay.cpp \
        $$PixelEngine_srcPath/display/pixel.cpp \
        $$PixelEngine_srcPath/gameobject/collider/basic/collider.cpp \
        $$PixelEngine_srcPath/gameobject/painter/basic/painter.cpp \
        $$PixelEngine_srcPath/gameobject/painter/spritePainter.cpp \
        $$PixelEngine_srcPath/gameobject/painter/hitboxPainter.cpp \
        $$PixelEngine_srcPath/gameobject/controller/basic/controller.cpp \
        $$PixelEngine_srcPath/gameobject/controller/keyController.cpp \
        $$PixelEngine_srcPath/gameobject/basic/gameobject.cpp \
        $$PixelEngine_srcPath/gameobject/property/property.cpp \
        $$PixelEngine_srcPath/gameobject/sensor/basic/sensor.cpp \
        $$PixelEngine_srcPath/gameobject/wall.cpp \
        $$PixelEngine_srcPath/gameobject/texture/texture.cpp \
        $$PixelEngine_srcPath/gameobject/texture/animatedTexture.cpp \
        $$PixelEngine_srcPath/utility/group/gameObjectGroup.cpp \
        $$PixelEngine_srcPath/utility/event.cpp \
        $$PixelEngine_srcPath/utility/userEventHandler.cpp \
        $$PixelEngine_srcPath/utility/timer.cpp \
        $$PixelEngine_srcPath/utility/layeritem.cpp

HEADERS += \
        $$PixelEngine_incPath/gameobject/painter/colliderPainter.h \
        $$PixelEngine_incPath/gameobject/painter/textPainter.h \
        $$PixelEngine_incPath/gameobject/painter/vertexPathPainter.h \
        $$PixelEngine_incPath/utility/base.h \
        $$PixelEngine_incPath/utility/group/objectTree.h \
        $$PixelEngine_incPath/utility/signalSubscriber.h \
        $$PixelEngine_incPath/display/drawUtilities.h \
        $$PixelEngine_incPath/gameobject/painter/texturePainter.h \
        $$PixelEngine_incPath/utility/mathFunctions.h \
        $$PixelEngine_incPath/utility/group/InteractiveGameObject.h \
        $$PixelEngine_incPath/utility/group/InteractiveGameObjectGroup.h \
        $$PixelEngine_incPath/utility/group/groupManagerInterface.h \
        $$PixelEngine_incPath/utility/profiler.h \
        $$PixelEngine_incPath/gameobject/painter/pixelPainter.h \
        $$PixelEngine_incPath/gameobject/controller/basic/dynamicCoordinator.h \
        $$PixelEngine_incPath/gameobject/property/body.h \
        $$PixelEngine_incPath/gameobject/property/food.h \
        $$PixelEngine_incPath/gameobject/property/mood.h \
        $$PixelEngine_incPath/gameobject/property/objectType.h \
        $$PixelEngine_incPath/utility/gameObjectEventHandler.h \
        $$PixelEngine_incPath/pixelengine.h \
        $$PixelEngine_incPath/display/pixelDisplay.h \
        $$PixelEngine_incPath/display/pixel.h \
        $$PixelEngine_incPath/gameobject/collider/basic/collider.h \
        $$PixelEngine_incPath/gameobject/painter/basic/painter.h \
        $$PixelEngine_incPath/gameobject/painter/spritePainter.h \
        $$PixelEngine_incPath/gameobject/painter/hitboxPainter.h \
        $$PixelEngine_incPath/gameobject/controller/basic/controller.h \
        $$PixelEngine_incPath/gameobject/controller/keyController.h \
        $$PixelEngine_incPath/gameobject/basic/gameobject.h \
        $$PixelEngine_incPath/gameobject/property/property.h \
        $$PixelEngine_incPath/gameobject/sensor/basic/sensor.h \
        $$PixelEngine_incPath/gameobject/texture/texture.h \
        $$PixelEngine_incPath/gameobject/texture/animatedTexture.h \
        $$PixelEngine_incPath/gameobject/wall.h \
        $$PixelEngine_incPath/utility/event.h \
        $$PixelEngine_incPath/utility/userEventHandler.h \
        $$PixelEngine_incPath/utility/group/gameObjectGroup.h \
        $$PixelEngine_incPath/utility/point.h \
        $$PixelEngine_incPath/utility/timer.h \
        $$PixelEngine_incPath/utility/rect.h \
        $$PixelEngine_incPath/utility/keyboard.h \
        $$PixelEngine_incPath/utility/layeritem.h

message( "----------------------------- " )
