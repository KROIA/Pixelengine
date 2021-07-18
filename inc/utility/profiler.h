#ifndef PROFILER_H
#define PROFILER_H

#if defined __has_include
#  if __has_include (<pixelEngineSettings.h>)
#    include <pixelEngineSettings.h>
#    pragma message( "Applying Profiler settings from  pixelEngineSettings.h " )
#  else
#ifdef BUILD_WITH_EASY_PROFILER

   #define PROFILE_ALL


  // #define GAME_OBJECT_PROFILER
  // #define SUBMODULE_PROFILER
  // #define SENSOR_PROFILER
  // #define PAINTER_PROFILER
  // #define TEXTURE_PROFILER
  // #define COLLIDER_PROFILER
  // #define CONTROLLER_PROFILER
  // #define EVENT_PROFILER
  // #define TIMER_PROFILER

  //  #define THREAD_PROFILER
    #define ENGINE_PROFILER
    #define ENGINE_DEEP_TICK_PROFILER
  //  #define DISPLAY_PROFILER
  //  #define MATHFUNCTION_PROFILER
    #define LEVEL_PROFILER
    #define MAIN_PROFILER

#pragma message( "Applying Profiler settings from " __FILE__ )
#endif
#endif
#endif

// Profiler
#include "easy/profiler.h"
#include "easy/arbitrary_value.h"
#include "easy/reader.h"




// Specific Profiler for each class

#if defined(GAME_OBJECT_PROFILER) || defined(PROFILE_ALL)
    #define GAME_OBJECT_FUNCTION(...) EASY_FUNCTION(EASY_FUNC_NAME, ## __VA_ARGS__)
    #define GAME_OBJECT_BLOCK(name, ...) EASY_BLOCK(name,  ## __VA_ARGS__)
    #define GAME_OBJECT_END_BLOCK EASY_END_BLOCK
#else
    #define GAME_OBJECT_FUNCTION(...)
    #define GAME_OBJECT_BLOCK(...)
    #define GAME_OBJECT_END_BLOCK
#endif

#if defined(SUBMODULE_PROFILER) || defined(PROFILE_ALL)
    #define SUBMODULE_FUNCTION(...) EASY_FUNCTION(EASY_FUNC_NAME, ## __VA_ARGS__)
    #define SUBMODULE_BLOCK(name, ...) EASY_BLOCK(name,  ## __VA_ARGS__)
    #define SUBMODULE_END_BLOCK EASY_END_BLOCK
#else
    #define SUBMODULE_FUNCTION(...)
    #define SUBMODULE_BLOCK(...)
    #define SUBMODULE_END_BLOCK
#endif

#if defined(SENSOR_PROFILER) || defined(PROFILE_ALL)
    #define SENSOR_FUNCTION(...) EASY_FUNCTION(EASY_FUNC_NAME, ## __VA_ARGS__)
    #define SENSOR_BLOCK(name, ...) EASY_BLOCK(name,  ## __VA_ARGS__)
    #define SENSOR_END_BLOCK EASY_END_BLOCK
#else
    #define SENSOR_FUNCTION(...)
    #define SENSOR_BLOCK(...)
    #define SENSOR_END_BLOCK
#endif

#if defined(PAINTER_PROFILER) || defined(PROFILE_ALL)
    #define PAINTER_FUNCTION(...) EASY_FUNCTION(EASY_FUNC_NAME, ## __VA_ARGS__)
    #define PAINTER_BLOCK(name, ...) EASY_BLOCK(name,  ## __VA_ARGS__)
    #define PAINTER_END_BLOCK EASY_END_BLOCK
#else
    #define PAINTER_FUNCTION(...)
    #define PAINTER_BLOCK(...)
    #define PAINTER_END_BLOCK
#endif

#if defined(TEXTURE_PROFILER) || defined(PROFILE_ALL)
    #define TEXTURE_FUNCTION(...) EASY_FUNCTION(EASY_FUNC_NAME, ## __VA_ARGS__)
    #define TEXTURE_BLOCK(name, ...) EASY_BLOCK(name,  ## __VA_ARGS__)
    #define TEXTURE_END_BLOCK EASY_END_BLOCK
#else
    #define TEXTURE_FUNCTION(...)
    #define TEXTURE_BLOCK(...)
    #define TEXTURE_END_BLOCK
#endif

#if defined(COLLIDER_PROFILER) || defined(PROFILE_ALL)
    #define COLLIDER_FUNCTION(...) EASY_FUNCTION(EASY_FUNC_NAME, ## __VA_ARGS__)
    #define COLLIDER_BLOCK(name, ...) EASY_BLOCK(name,  ## __VA_ARGS__)
    #define COLLIDER_END_BLOCK EASY_END_BLOCK
#else
    #define COLLIDER_FUNCTION(...)
    #define COLLIDER_BLOCK(...)
    #define COLLIDER_END_BLOCK
#endif

#if defined(CONTROLLER_PROFILER) || defined(PROFILE_ALL)
    #define CONTROLLER_FUNCTION(...) EASY_FUNCTION(EASY_FUNC_NAME, ## __VA_ARGS__)
    #define CONTROLLER_BLOCK(name, ...) EASY_BLOCK(name,  ## __VA_ARGS__)
    #define CONTROLLER_END_BLOCK EASY_END_BLOCK
#else
    #define CONTROLLER_FUNCTION(...)
    #define CONTROLLER_BLOCK(...)
    #define CONTROLLER_END_BLOCK
#endif

#if defined(EVENT_PROFILER) || defined(PROFILE_ALL)
    #define EVENT_FUNCTION(...) EASY_FUNCTION(EASY_FUNC_NAME, ## __VA_ARGS__)
    #define EVENT_BLOCK(name, ...) EASY_BLOCK(name,  ## __VA_ARGS__)
    #define EVENT_END_BLOCK EASY_END_BLOCK
#else
    #define EVENT_FUNCTION(...)
    #define EVENT_BLOCK(...)
    #define EVENT_END_BLOCK
#endif

#if defined(TIMER_PROFILER) || defined(PROFILE_ALL)
    #define TIMER_FUNCTION(...) EASY_FUNCTION(EASY_FUNC_NAME, ## __VA_ARGS__)
    #define TIMER_BLOCK(name, ...) EASY_BLOCK(name,  ## __VA_ARGS__)
    #define TIMER_END_BLOCK EASY_END_BLOCK
#else
    #define TIMER_FUNCTION(...)
    #define TIMER_BLOCK(...)
    #define TIMER_END_BLOCK
#endif



#if defined(THREAD_PROFILER) || defined(PROFILE_ALL)
    #define THREAD_FUNCTION(...) EASY_FUNCTION(EASY_FUNC_NAME, ## __VA_ARGS__)
    #define THREAD_BLOCK(name, ...) EASY_BLOCK(name,  ## __VA_ARGS__)
    #define THREAD_END_BLOCK EASY_END_BLOCK
    #define THREAD(name) EASY_THREAD(name)
#else
    #define THREAD_FUNCTION(...)
    #define THREAD_BLOCK(...)
    #define THREAD_END_BLOCK
    #define THREAD(name)
#endif

#if defined(ENGINE_PROFILER) || defined(PROFILE_ALL)
    #define ENGINE_FUNCTION(...) EASY_FUNCTION(EASY_FUNC_NAME, ## __VA_ARGS__)
    #define ENGINE_BLOCK(name, ...) EASY_BLOCK(name,  ## __VA_ARGS__)
    #define ENGINE_END_BLOCK EASY_END_BLOCK
#else
    #define ENGINE_FUNCTION(...)
    #define ENGINE_BLOCK(...)
    #define ENGINE_END_BLOCK
#endif

#if defined(ENGINE_DEEP_TICK_PROFILER) || defined(PROFILE_ALL)
    #define ENGINE_DEEP_TICK_FUNCTION(...) EASY_FUNCTION(EASY_FUNC_NAME, ## __VA_ARGS__)
    #define ENGINE_DEEP_TICK_BLOCK(name, ...) EASY_BLOCK(name,  ## __VA_ARGS__)
    #define ENGINE_DEEP_TICK_END_BLOCK EASY_END_BLOCK
#else
    #define ENGINE_DEEP_TICK_FUNCTION(...)
    #define ENGINE_DEEP_TICK_BLOCK(...)
    #define ENGINE_DEEP_TICK_END_BLOCK
#endif

#if defined(DISPLAY_PROFILER) || defined(PROFILE_ALL)
    #define DISPLAY_FUNCTION(...) EASY_FUNCTION(EASY_FUNC_NAME, ## __VA_ARGS__)
    #define DISPLAY_BLOCK(name, ...) EASY_BLOCK(name,  ## __VA_ARGS__)
    #define DISPLAY_END_BLOCK EASY_END_BLOCK
#else
    #define DISPLAY_FUNCTION(...)
    #define DISPLAY_BLOCK(...)
    #define DISPLAY_END_BLOCK
#endif

#if defined(MATHFUNCTION_PROFILER) || defined(PROFILE_ALL)
    #define MATHFUNCTION_FUNCTION(...) EASY_FUNCTION(EASY_FUNC_NAME, ## __VA_ARGS__)
    #define MATHFUNCTION_BLOCK(name, ...) EASY_BLOCK(name,  ## __VA_ARGS__)
    #define MATHFUNCTION_END_BLOCK EASY_END_BLOCK
#else
    #define MATHFUNCTION_FUNCTION(...)
    #define MATHFUNCTION_BLOCK(...)
    #define MATHFUNCTION_END_BLOCK
#endif

#if defined(LEVEL_PROFILER) || defined(PROFILE_ALL)
    #define LEVEL_FUNCTION(...) EASY_FUNCTION(EASY_FUNC_NAME, ## __VA_ARGS__)
    #define LEVEL_BLOCK(name, ...) EASY_BLOCK(name,  ## __VA_ARGS__)
    #define LEVEL_END_BLOCK EASY_END_BLOCK
#else
    #define LEVEL_FUNCTION(...)
    #define LEVEL_BLOCK(...)
    #define LEVEL_END_BLOCK
#endif

#if defined(MAIN_PROFILER) || defined(PROFILE_ALL)
    #define MAIN_FUNCTION(...) EASY_FUNCTION(EASY_FUNC_NAME, ## __VA_ARGS__)
    #define MAIN_BLOCK(name, ...) EASY_BLOCK(name,  ## __VA_ARGS__)
    #define MAIN_END_BLOCK EASY_END_BLOCK
#else
    #define MAIN_FUNCTION(...)
    #define MAIN_BLOCK(...)
    #define MAIN_END_BLOCK
#endif

#endif // PROFILER_H
