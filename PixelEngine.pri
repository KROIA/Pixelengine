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

LIBS += -lopengl32 -lglu32 -lComdlg32


include(extern/easy_profiler.pri)
include(extern/SFML.pri)

PixelEngine_incPath = $$ENGINE_PATH/inc
PixelEngine_srcPath = $$ENGINE_PATH/src

INCLUDEPATH += $$incPath \
               $$PixelEngine_incPath \
               $$PixelEngine_incPath/utility \
               $$PixelEngine_incPath/utility/group \
               $$PixelEngine_incPath/utility/group/chunk \
               $$PixelEngine_incPath/utility/baseClasses \
               $$PixelEngine_incPath/utility/generalFunctionality \
               $$PixelEngine_incPath/utility/generalFunctionality/extern \
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
               $$PixelEngine_incPath/gameobject/event \
               $$PixelEngine_incPath/gameobject/event/basic \
               $$PixelEngine_incPath/display

SOURCES += \
        $$PWD/src/gameobject/event/basic/buttonEvent.cpp \
        $$PWD/src/gameobject/event/mouseButtonEvent.cpp \
        $$PixelEngine_srcPath/gameobject/event/mouseMoveEvent.cpp \
        $$PixelEngine_srcPath/gameobject/controller/mouseController.cpp \
        $$PixelEngine_srcPath/gameobject/basic/submodule.cpp \
        $$PixelEngine_srcPath/gameobject/sensor/laserSensor.cpp \
        $$PixelEngine_srcPath/gameobject/sensor/rectSensor.cpp \
        $$PixelEngine_srcPath/gameobject/painter/colliderPainter.cpp \
        $$PixelEngine_srcPath/gameobject/painter/textPainter.cpp \
        $$PixelEngine_srcPath/gameobject/painter/vertexPathPainter.cpp \
        $$PixelEngine_srcPath/utility/group/objectTree.cpp \
        $$PixelEngine_srcPath/utility/settings.cpp \
        $$PixelEngine_srcPath/display/drawUtilities.cpp \
        $$PixelEngine_srcPath/gameobject/painter/texturePainter.cpp \
        $$PixelEngine_srcPath/utility/group/InteractiveGameObject.cpp \
        $$PixelEngine_srcPath/utility/group/InteractiveGameObjectGroup.cpp \
        $$PixelEngine_srcPath/gameobject/painter/pixelpainter.cpp \
        $$PixelEngine_srcPath/pixelengine.cpp \
        $$PixelEngine_srcPath/display/pixelDisplay.cpp \
        $$PixelEngine_srcPath/display/pixel.cpp \
        $$PixelEngine_srcPath/gameobject/collider/basic/collider.cpp \
        $$PixelEngine_srcPath/gameobject/painter/basic/painter.cpp \
        $$PixelEngine_srcPath/gameobject/painter/spritePainter.cpp \
        $$PixelEngine_srcPath/gameobject/controller/basic/controller.cpp \
        $$PixelEngine_srcPath/gameobject/controller/keyController.cpp \
        $$PixelEngine_srcPath/gameobject/basic/gameobject.cpp \
        $$PixelEngine_srcPath/gameobject/property/property.cpp \
        $$PixelEngine_srcPath/gameobject/sensor/basic/sensor.cpp \
        $$PixelEngine_srcPath/gameobject/wall.cpp \
        $$PixelEngine_srcPath/gameobject/texture/texture.cpp \
        $$PixelEngine_srcPath/gameobject/texture/animatedTexture.cpp \
        $$PixelEngine_srcPath/gameobject/event/basic/event.cpp \
        $$PixelEngine_srcPath/utility/group/gameObjectGroup.cpp \
        $$PixelEngine_srcPath/gameobject/event/keyEvent.cpp \
        $$PixelEngine_srcPath/utility/baseClasses/userEventHandler.cpp \
        $$PixelEngine_srcPath/utility/baseClasses/timer.cpp \
        $$PixelEngine_srcPath/utility/baseClasses/layeritem.cpp \
        $$PixelEngine_srcPath/utility/generalFunctionality/fileBrowser.cpp

HEADERS += \
        $$PWD/inc/gameobject/event/basic/buttonEvent.h \
        $$PWD/inc/gameobject/event/mouseButtonEvent.h \
        $$PixelEngine_incPath/gameobject/controller/mouseController.h \
        $$PixelEngine_incPath/gameobject/event/mouseMoveEvent.h \
        $$PixelEngine_incPath/utility/generalFunctionality/fileBrowser.h \
        $$PixelEngine_incPath/display/displayInterface.h \
        $$PixelEngine_incPath/gameobject/basic/submodule.h \
        $$PixelEngine_incPath/gameobject/sensor/laserSensor.h \
        $$PixelEngine_incPath/gameobject/sensor/rectSensor.h \
        $$PixelEngine_incPath/utility/debug.h \
        $$PixelEngine_incPath/gameobject/painter/colliderPainter.h \
        $$PixelEngine_incPath/gameobject/painter/textPainter.h \
        $$PixelEngine_incPath/gameobject/painter/vertexPathPainter.h \
        $$PixelEngine_incPath/utility/base.h \
        $$PixelEngine_incPath/utility/group/objectTree.h \
        $$PixelEngine_incPath/utility/baseClasses/signalEmitter.h \
        $$PixelEngine_incPath/display/drawUtilities.h \
        $$PixelEngine_incPath/gameobject/painter/texturePainter.h \
        $$PixelEngine_incPath/utility/generalFunctionality/mathFunctions.h \
        $$PixelEngine_incPath/utility/group/InteractiveGameObject.h \
        $$PixelEngine_incPath/utility/group/InteractiveGameObjectGroup.h \
        $$PixelEngine_incPath/utility/group/groupManagerInterface.h \
        $$PixelEngine_incPath/utility/profiler.h \
        $$PixelEngine_incPath/gameobject/painter/pixelPainter.h \
        $$PixelEngine_incPath/gameobject/property/body.h \
        $$PixelEngine_incPath/gameobject/property/food.h \
        $$PixelEngine_incPath/gameobject/property/mood.h \
        $$PixelEngine_incPath/gameobject/property/objectType.h \
        $$PixelEngine_incPath/utility/baseClasses/engineInterface.h \
        $$PixelEngine_incPath/pixelengine.h \
        $$PixelEngine_incPath/display/pixelDisplay.h \
        $$PixelEngine_incPath/display/pixel.h \
        $$PixelEngine_incPath/gameobject/collider/basic/collider.h \
        $$PixelEngine_incPath/gameobject/painter/basic/painter.h \
        $$PixelEngine_incPath/gameobject/painter/spritePainter.h \
        $$PixelEngine_incPath/gameobject/controller/basic/controller.h \
        $$PixelEngine_incPath/gameobject/controller/keyController.h \
        $$PixelEngine_incPath/gameobject/basic/gameobject.h \
        $$PixelEngine_incPath/gameobject/property/property.h \
        $$PixelEngine_incPath/gameobject/sensor/basic/sensor.h \
        $$PixelEngine_incPath/gameobject/texture/texture.h \
        $$PixelEngine_incPath/gameobject/texture/animatedTexture.h \
        $$PixelEngine_incPath/gameobject/wall.h \
        $$PixelEngine_incPath/gameobject/event/basic/event.h \
        $$PixelEngine_incPath/gameobject/event/keyEvent.h \
        $$PixelEngine_incPath/utility/baseClasses/userEventHandler.h \
        $$PixelEngine_incPath/utility/group/gameObjectGroup.h \
        $$PixelEngine_incPath/utility/baseClasses/timer.h \
        $$PixelEngine_incPath/utility/baseClasses/rect.h \
        $$PixelEngine_incPath/utility/baseClasses/keyboard.h \
        $$PixelEngine_incPath/utility/baseClasses/layeritem.h \
        $$PixelEngine_incPath/utility/generalFunctionality/extern/FastNoiseLite.h

message( "----------------------------- " )
