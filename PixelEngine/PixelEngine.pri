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
SFML_PATH               = "$$ENGINE_PATH/extern/SFML"
SFML_DEBUG_DLL_BASE     = $$SFML_PATH\bin\Debug\lib    # Path to the dll's from SFML
SFML_RELEASE_DLL_BASE   = $$SFML_PATH\bin\Release\lib  # Path to the dll's from SFML
isEmpty(SFML_PATH) {
    SFML_PATH = $$PWD/PixelEngine/extern/SFML
} else {
    message( 'SFML_PATH is not empty: \"$${SFML_PATH}\"' )
}

sfml_includePath  = "$$SFML_PATH/include"
sfml_binPath      = "$$SFML_PATH/bin"
sfml_libs_debug   = "$$sfml_binPath/Debug/lib/libsfml-audio-d.a" \
                    "$$sfml_binPath/Debug/lib/libsfml-graphics-d.a" \
                    "$$sfml_binPath/Debug/lib/libsfml-main-d.a" \
                    "$$sfml_binPath/Debug/lib/libsfml-network-d.a" \
                    "$$sfml_binPath/Debug/lib/libsfml-system-d.a" \
                    "$$sfml_binPath/Debug/lib/libsfml-window-d.a"

sfml_libs_release = "$$sfml_binPath/Release/lib/libsfml-audio.a" \
                    "$$sfml_binPath/Release/lib/libsfml-graphics.a" \
                    "$$sfml_binPath/Release/lib/libsfml-main.a" \
                    "$$sfml_binPath/Release/lib/libsfml-network.a" \
                    "$$sfml_binPath/Release/lib/libsfml-system.a" \
                    "$$sfml_binPath/Release/lib/libsfml-window.a"

# Copy dll's from SFML to the bin dir
CONFIG(debug, debug|release) {
    isEmpty(SFML_DEBUG_DLL_BASE) {
        SFML_DEBUG_DLL_BASE = $$SFML_PATH\bin\Debug\lib
    }
SFML_DEBUG_DLL_BASE ~= s,/,\\,g # Replace "/" with "\\"
message( "Copy debug dll\'s: $$SFML_DEBUG_DLL_BASE" )
QMAKE_PRE_LINK = copy "$$SFML_DEBUG_DLL_BASE\sfml*.dll" "debug\sfml*.dll"
}else{
    isEmpty(SFML_RELEASE_DLL_BASE) {
        SFML_RELEASE_DLL_BASE = $$SFML_PATH\bin\Release\lib
    }
SFML_RELEASE_DLL_BASE ~= s,/,\\,g # Replace "/" with "\\"
message( "Copy release dll\'s $$SFML_RELEASE_DLL_BASE" )
QMAKE_PRE_LINK = copy "$$SFML_RELEASE_DLL_BASE\sfml*.dll" "release\sfml*.dll"
}


CONFIG(release, debug|release): sfml_libs = $$sfml_libs_release
CONFIG(debug, debug|release):   sfml_libs = $$sfml_libs_debug
LIBS        += $$sfml_libs
INCLUDEPATH += $$sfml_includePath
DEPENDPATH  += $$sfml_includePath
# End SFML stuff

PixelEngine_incPath = $$ENGINE_PATH/inc
PixelEngine_srcPath = $$ENGINE_PATH/src

INCLUDEPATH += $$incPath \
               $$PixelEngine_incPath \
               $$PixelEngine_incPath/utility \
               $$PixelEngine_incPath/utility/group \
               $$PixelEngine_incPath/gameobject \
               $$PixelEngine_incPath/gameobject/basic \
               $$PixelEngine_incPath/gameobject/collider \
               $$PixelEngine_incPath/gameobject/collider/basic \
               $$PixelEngine_incPath/gameobject/controller \
               $$PixelEngine_incPath/gameobject/controller/basic \
               $$PixelEngine_incPath/gameobject/painter \
               $$PixelEngine_incPath/gameobject/painter/basic \
               $$PixelEngine_incPath/gameobject/property/ \
               $$PixelEngine_incPath/display

SOURCES += \
        $$PixelEngine_srcPath/pixelengine.cpp \
        $$PixelEngine_srcPath/display/pixelDisplay.cpp \
        $$PixelEngine_srcPath/display/pixel.cpp \
        $$PixelEngine_srcPath/gameobject/collider/basic/collider.cpp \
        $$PixelEngine_srcPath/gameobject/painter/basic/painter.cpp \
        $$PixelEngine_srcPath/gameobject/painter/hitboxPainter.cpp \
        $$PixelEngine_srcPath/gameobject/controller/basic/controller.cpp \
        $$PixelEngine_srcPath/gameobject/controller/keyController.cpp \
        $$PixelEngine_srcPath/gameobject/basic/gameobject.cpp \
        $$PixelEngine_srcPath/gameobject/property/property.cpp \
        $$PixelEngine_srcPath/gameobject/wall.cpp \
        $$PixelEngine_srcPath/utility/group/gameObjectGroup.cpp \
        $$PixelEngine_srcPath/utility/event.cpp \
        $$PixelEngine_srcPath/utility/eventhandler.cpp \
        $$PixelEngine_srcPath/utility/timer.cpp \
        $$PixelEngine_srcPath/utility/layeritem.cpp

HEADERS += \
        $$PWD/inc/gameobject/property/body.h \
        $$PWD/inc/gameobject/property/food.h \
        $$PWD/inc/gameobject/property/mood.h \
        $$PWD/inc/gameobject/property/objectType.h \
        $$PixelEngine_incPath/pixelengine.h \
        $$PixelEngine_incPath/display/pixelDisplay.h \
        $$PixelEngine_incPath/display/pixel.h \
        $$PixelEngine_incPath/gameobject/collider/basic/collider.h \
        $$PixelEngine_incPath/gameobject/painter/basic/painter.h \
        $$PixelEngine_incPath/gameobject/painter/hitboxPainter.h \
        $$PixelEngine_incPath/gameobject/controller/basic/controller.h \
        $$PixelEngine_incPath/gameobject/controller/keyController.h \
        $$PixelEngine_incPath/gameobject/basic/gameobject.h \
        $$PixelEngine_incPath/gameobject/property/property.h \
        $$PixelEngine_incPath/gameobject/wall.h \
        $$PixelEngine_incPath/utility/event.h \
        $$PixelEngine_incPath/utility/eventhandler.h \
        $$PixelEngine_incPath/utility/group/gameObjectGroup.h \
        $$PixelEngine_incPath/utility/point.h \
        $$PixelEngine_incPath/utility/vector.h \
        $$PixelEngine_incPath/utility/timer.h \
        $$PixelEngine_incPath/utility/rect.h \
        $$PixelEngine_incPath/utility/keyboard.h \
        $$PixelEngine_incPath/utility/layeritem.h
