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



# SFML stuff
sfml_version      = "2.5.1"

sfml_basePath     = "../../extern/SFML-$$sfml_version"
sfml_includePath  = "$$sfml_basePath/include"
sfml_binPath      = "$$sfml_basePath/bin"
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

CONFIG(release, debug|release): sfml_libs = $$sfml_libs_release
CONFIG(debug, debug|release):   sfml_libs = $$sfml_libs_debug
LIBS        += $$sfml_libs
INCLUDEPATH += $$sfml_includePath
DEPENDPATH  += $$sfml_includePath
# End SFML stuff

incPath = inc
srcPath = src

INCLUDEPATH += $$incPath \
               $$incPath/engine \
               $$incPath/engine/utility \
               $$incPath/engine/gameobject \
               $$incPath/engine/display

SOURCES += \
        main.cpp \
        $$srcPath/engine/display/pixelDisplay.cpp \
        $$srcPath/engine/utility/point.cpp \
        $$srcPath/engine/utility/vector.cpp \
        $$srcPath/engine/utility/timer.cpp \
        $$srcPath/engine/gameobject/collider.cpp \
        $$srcPath/engine/gameobject/painter.cpp \
        $$srcPath/engine/gameobject/controller.cpp \
        $$srcPath/engine/utility/rect.cpp \
        $$srcPath/engine/pixelengine.cpp \
        $$srcPath/engine/display/pixel.cpp \
        src/engine/gameobject/eventhandler.cpp \
        src/engine/utility/event.cpp \
        src/engine/utility/layeritem.cpp

HEADERS += \
        $$incPath/engine/display/pixelDisplay.h \
        $$incPath/engine/utility/point.h \
        $$incPath/engine/utility/vector.h \
        $$incPath/engine/utility/timer.h \
        $$incPath/engine/gameobject/collider.h \
        $$incPath/engine/gameobject/painter.h \
        $$incPath/engine/gameobject/controller.h \
        $$incPath/engine/utility/rect.h \
        $$incPath/engine/pixelengine.h \
        $$incPath/engine/display/pixel.h \
        inc/engine/gameobject/eventhandler.h \
        inc/engine/utility/event.h \
        inc/engine/utility/layeritem.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
