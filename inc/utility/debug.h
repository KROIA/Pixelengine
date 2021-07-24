#ifndef DEBUG_H
#define DEBUG_H
#if defined __has_include
#  if __has_include (<pixelEngineSettings.h>)
#    include <pixelEngineSettings.h>
//#    pragma message( "Applying Profiler settings from  pixelEngineSettings.h " )
#  else

#  endif
#endif

#include <QDebug>


#endif // DEBUG_H
