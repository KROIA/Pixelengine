#include "pixelengine.h"


ObjectTree::Settings ObjectTree::__defaultSettings
{
    .boundry        = RectF(0,0,1000,1000),
    .maxObjects     = 128,
    .maxDepth       = 10,
    .parentDepth    = 0
};
InteractiveGameObject::Settings InteractiveGameObject::__defaultSettings
{
    .objectTree     = ObjectTree::__defaultSettings
};

PixelDisplay::Settings PixelDisplay::__defaultSettings
{
    .windowSize     = Vector2u(1080,720),
    .pixelMapSize   = Vector2u(100,100),
    .backgroundColor = Color(0,0,0),
    .sf_contextSettings = sf::ContextSettings(0,0,8,1,1,sf::ContextSettings::Default,false),
    .renderLayers   = RenderLayerIndex::__size
};
TextPainter::Settings TextPainter::__defaultSettings
{
    .isVisible      = false,
    .positionFix    = false,
    .position       = Vector2f(0,0),
    .fontPath       = "C:\\Windows\\Fonts\\consolab.ttf",
    .color          = Color(255,255,255,255),
    .characterSize  = 20,
    .renderLayer    = PixelDisplay::__defaultSettings.renderLayers-1
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
    .text       = TextPainter::__defaultSettings
};
