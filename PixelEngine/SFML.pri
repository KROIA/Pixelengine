

isEmpty(SFML_VERSION) {
    SFML_VERSION = "2.5.1"
    message( 'SFML_VERSION is empty. use default value: \"$$SFML_VERSION\"' )
} else {
    message( 'SFML_VERSION is not empty: \"$$SFML_VERSION\"' )
}
isEmpty(SFML_PATH) {
    SFML_PATH = $$PWD/PixelEngine/extern/SFML-$$SFML_VERSION
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
