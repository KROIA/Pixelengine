
profilerPath = $$PWD/easy_profiler


message( "----- easy_profiler.pri ----- " )
message( "  Path: $$profilerPath " )

# To enable the Profiler you can chose between two options:
# 1) "Projects" on the left side
#    Change the Build configuration to "Profile"
#    In the section "qmake: qmake.exe ProjectName.pro":
#     Add an additional parameter: "+ "CONFIG += BUILD_WITH_EASY_PROFILER""
#     without the " at the beginning and ending.
# 2) Define it in your .pro file using: CONFIG+=BUILD_WITH_EASY_PROFILER
BUILD_WITH_EASY_PROFILER{
    message( "  Profiler is active" )
    DEFINES += BUILD_WITH_EASY_PROFILER
}else{
    message( "  Profiler is not active" )
    message( "  If you want to enable the Profiler, define it in your .pro file using: CONFIG+=BUILD_WITH_EASY_PROFILER")
}


profilerBuildPath_debug   = "$$profilerPath/bin/Debug/bin"
profilerBuildPath_release = "$$profilerPath/bin/Release/bin"

profilerIncludePath = "$$profilerPath/easy_profiler_core/include"


profilerLib_release = "$$profilerBuildPath_release/libeasy_profiler.dll.a"
profilerLib_debug   = "$$profilerBuildPath_debug/libeasy_profiler.dll.a"


# Copy dll from the Profiler to the bin dir
CONFIG(debug, debug|release){
    profilerBuildPath_debug ~= s,/,\\,g # Replace "/" with "\\"
    message( "  Copy debug dll: $$profilerBuildPath_debug " )
    !isEmpty(QMAKE_POST_LINK){
    QMAKE_POST_LINK += " & "
    }
    QMAKE_POST_LINK += copy "\"$$profilerBuildPath_debug\libeasy_profiler.dll\"" "\"debug\libeasy_profiler.dll\""
}else{
    profilerBuildPath_release ~= s,/,\\,g # Replace "/" with "\\"
    message( "  Copy release dll: $$profilerBuildPath_release " )
    !isEmpty(QMAKE_POST_LINK){
    QMAKE_POST_LINK += " & "
    }
    QMAKE_POST_LINK += copy "\"$$profilerBuildPath_release\libeasy_profiler.dll\"" "\"release\libeasy_profiler.dll\""
}
message("  $$QMAKE_POST_LINK")

CONFIG(release, debug|release): profilerLib = $$profilerLib_release
CONFIG(debug, debug|release):   profilerLib = $$profilerLib_debug



LIBS        += $$profilerLib
INCLUDEPATH += $$profilerIncludePath
DEPENDPATH  += $$profilerIncludePath


message( "----------------------------- " )
