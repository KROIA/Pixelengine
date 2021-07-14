#include "pixelengine.h"


Chunk::Settings Chunk::__defaultSettings
{
    .size           = Vector2u(1,1),
    .position       = Vector2f(0,0),
    .chunkID        = ChunkID(false,Vector2<size_t>(0,0)),
    .isVisible      = false
};
ChunkMap::Settings ChunkMap::__defaultSettings
{
    .chunk          = Chunk::__defaultSettings,
    .chunkMapSize   = Vector2u(1,1),
    .position       = Vector2i(0,0)
};
InteractiveGameObject::Settings InteractiveGameObject::__defaultSettings
{
    .chunkMap       = ChunkMap::__defaultSettings
};
DisplayText::Settings DisplayText::__defaultSettings
{
    .isVisible      = false,
    .positionFix    = false,
    .position       = Vector2f(0,0),
    .fontPath       = "C:\\Windows\\Fonts\\consolab.ttf",
    .color          = Color(255,255,255,255),
    .characterSize  = 20
};
PixelDisplay::Settings PixelDisplay::__defaultSettings
{
    .windowSize     = Vector2u(1080,720),
    .pixelMapSize   = Vector2u(100,100),
    .backgroundColor = Color(0,0,0),
    .sf_contextSettings = sf::ContextSettings(0,0,8,1,1,sf::ContextSettings::Default,false)
};

PixelEngine::EngineSettings PixelEngine::__defaultEngineSettings
{
    .runInSync              = true,
    .time_syncInterval      = 0.02,
    .time_eventInterval     = 0.02,
    .time_tickInterval      = 0.02,
    .time_displayInterval   = 0.02,
    .statsDisplayFilter     = 0.8
};
PixelEngine::Settings PixelEngine::__defaultSettings
{
    .engine     = PixelEngine::__defaultEngineSettings,
    .gameObject = InteractiveGameObject::__defaultSettings,
    .display    = PixelDisplay::__defaultSettings,
    .text       = DisplayText::__defaultSettings
};
