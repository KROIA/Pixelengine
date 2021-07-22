#include "pixelDisplay.h"

PixelDisplay::PixelDisplay()
{
    constructor(__defaultSettings);
}
PixelDisplay::PixelDisplay(const Settings &settings)
{
    constructor(settings);
}
PixelDisplay::PixelDisplay(const Vector2u &windowSize,
                           const Vector2u &pixelMapSize,
                           const Color &backgroundColor)
{
    Settings settings           = __defaultSettings;
    settings.windowSize         = windowSize;
    settings.pixelMapSize       = pixelMapSize;
    settings.backgroundColor    = backgroundColor;

    constructor(settings);
}
void PixelDisplay::constructor(const Settings &settings)
{
    m_windowSize    = settings.windowSize;
    m_pixelMapSize  = settings.pixelMapSize;
    m_dragMap       = false;
    m_mutex         = PTHREAD_MUTEX_INITIALIZER;

   /* sf::ContextSettings settings;
    settings.antialiasingLevel = 8;*/
    m_renderWindow = new sf::RenderWindow(sf::VideoMode(m_windowSize.x,m_windowSize.y),
                                          "PixelDisplay",sf::Style::Default, settings.sf_contextSettings);
    //m_renderWindow->setVerticalSyncEnabled(true);
    //m_renderWindow->setActive(true);
    //m_renderWindow->setFramerateLimit(60);
    m_backgroundColor = settings.backgroundColor;

    m_localPixelPainter         = new PixelPainter();
    m_localPixelPainter->resize(m_pixelMapSize);
    m_localPixelPainter->setRenderLayer(0);
    m_localPixelPainter->setOriginType(Origin::topLeft);

    m_localPixlerUsed           = false;
    m_stats.renderSprites       = 0;
    m_stats.renderText          = 0;
    m_stats.renderVertexPaths   = 0;
    m_viewPortZoom              = 1;
    m_stats.activePainters      = 0;
    m_maxRenderLayers           = settings.renderLayers;
    m_renderLayerList.resize(m_maxRenderLayers);
    m_stats.avtivePaintersInLayer.resize(m_maxRenderLayers);
    for(size_t i=0; i<m_renderLayerList.size(); i++)
    {
        m_renderLayerList[i].index = i;
        m_renderLayerList[i].enabled = true;
        m_stats.avtivePaintersInLayer[i] = 0;

    }

    float zoomFac               = (float)m_pixelMapSize.x / (float)m_windowSize.x;
    zoomViewAt(Vector2i(0,0),zoomFac);

    clear();
}
PixelDisplay::PixelDisplay(const PixelDisplay &other)
{
     this->m_windowSize   = other.m_windowSize;
     this->m_pixelMapSize    = other.m_pixelMapSize;
     this->m_renderWindow = other.m_renderWindow;
     *this->m_localPixelPainter = *other.m_localPixelPainter;
     this->m_backgroundColor   = other.m_backgroundColor;
}
PixelDisplay::~PixelDisplay()
{
    m_renderWindow->close();
    delete m_renderWindow;
}
PixelDisplay::Settings PixelDisplay::getSettings() const
{
    Settings settings;
    settings.backgroundColor    = m_backgroundColor;
    settings.pixelMapSize       = m_pixelMapSize;
    settings.windowSize         = m_windowSize;
    settings.renderLayers       = m_maxRenderLayers;
    return settings;
}
void PixelDisplay::setIcon(const sf::Image &image)
{
    m_renderWindow->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
}
bool PixelDisplay::setIcon(const string &imagePath)
{
    auto image = sf::Image{};
    if (!image.loadFromFile(imagePath))
    {
        // Error handling...
        return false;
    }
    setIcon(image);
    return true;
}
void PixelDisplay::setTitle(const string &title)
{
    m_renderWindow->setTitle(title);
}


void PixelDisplay::display()
{
    DISPLAY_FUNCTION("PixelDisplay::display()",profiler::colors::Blue);

    m_renderWindow->clear();

    m_stats.renderSprites       = 0;
    m_stats.renderText          = 0;
    m_stats.renderVertexPaths   = 0;
    if(m_localPixlerUsed)
    {
        m_localPixelPainter->render(m_renderWindow,m_viewPortZoom,m_stats);
        m_stats.activePainters++;
    }
    for(size_t i=0; i<m_renderLayerList.size();  i++)
    {
        if(!m_renderLayerList[i].enabled)
            continue;
        for(auto pair : m_renderLayerList[i].table)
        {
            if(pair.second->needsRendering(m_renderFrame))
                pair.second->render(m_renderWindow,m_viewPortZoom,m_stats);
        }
    }
    DISPLAY_BLOCK("m_renderWindow->display()",profiler::colors::Blue100);
    m_renderWindow->display();
    DISPLAY_END_BLOCK;
    clear();
}
void PixelDisplay::clear()
{
    DISPLAY_FUNCTION(profiler::colors::Blue100);
    if(m_localPixlerUsed)
    {
        m_localPixelPainter->clear();
        m_localPixlerUsed = false;
        m_stats.activePainters--;
    }
}
void PixelDisplay::setLayerVisibility(size_t layer, bool visibility)
{
    if(layer >= m_renderLayerList.size())
        return;
    m_renderLayerList[layer].enabled = visibility;
}
bool PixelDisplay::getLayerVisibility(size_t layer)
{
    if(layer >= m_renderLayerList.size())
        return false;
    return m_renderLayerList[layer].enabled;
}

void PixelDisplay::setPixel(const Vector2u &pos, const Color &color)
{
    DISPLAY_FUNCTION(profiler::colors::Blue200);
    m_localPixelPainter->setPixelColor(pos,color);
    m_localPixlerUsed = true;
}
void PixelDisplay::setPixel(const Pixel &pixel)
{
    DISPLAY_FUNCTION(profiler::colors::Blue300);
    m_localPixelPainter->setPixel(pixel);
    m_localPixlerUsed = true;
}
void PixelDisplay::setPixel(const vector<Pixel> &pixelList)
{
    DISPLAY_FUNCTION(profiler::colors::Blue400);
    for(size_t i=0; i<pixelList.size(); i++)
    {
        m_localPixelPainter->setPixel(pixelList[i]);
    }
    m_localPixlerUsed = true;
}



bool PixelDisplay::isOpen() const
{
    return m_renderWindow->isOpen();
}

void PixelDisplay::handleEvents()
{
    DISPLAY_FUNCTION(profiler::colors::Blue500);
    if(!m_renderWindow->isOpen())
    {
        return;
    }
    sf::Event event;
    event.type = sf::Event::EventType::Count;

    m_lastEventList.clear();
    while(m_renderWindow->pollEvent(event))
    {
        m_lastEventList.push_back(event);
        switch(event.type)
        {
            case sf::Event::Closed:
            {
                m_renderWindow->close();
                break;
            }
            case sf::Event::Resized:
            {
                m_renderWindow->setSize(m_windowSize);
                m_renderWindow->setView(m_view);
                break;
            }
            case sf::Event::LostFocus:{
                std::cout << "Lost" << std::endl;
                break;}
            case sf::Event::GainedFocus:{
                std::cout << "Gained" << std::endl;
                break;}
            case sf::Event::TextEntered:{break;}
            case sf::Event::KeyPressed:{break;}
            case sf::Event::KeyReleased:{break;}
            case sf::Event::MouseWheelMoved:{break;}
            case sf::Event::MouseWheelScrolled:
            {
                float zoomFactor = 0.9;
                if (event.mouseWheelScroll.delta < 0)
                        zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, (1.f / zoomFactor));
                    else if (event.mouseWheelScroll.delta > 0)
                        zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, zoomFactor);
                break;
            }
            case sf::Event::MouseButtonPressed:{
                if(event.mouseButton.button == sf::Mouse::Button::Middle)
                {
                    m_dragMap = true;
                }

                break;}
            case sf::Event::MouseButtonReleased:{
                if(event.mouseButton.button == sf::Mouse::Button::Middle)
                {
                    m_dragMap = false;
                }
                break;}
            case sf::Event::MouseMoved:{
                if(m_dragMap)
                {
                    Vector2f movingVec =  m_lastMousePos - Vector2f(event.mouseMove.x,event.mouseMove.y);
                    movingVec.x *= m_viewPortZoom;
                    movingVec.y *= m_viewPortZoom;
                    m_view = m_renderWindow->getView() ;
                    m_view.move(movingVec);
                    m_renderWindow->setView(m_view);
                    updateRenderFrame();
                }
                m_lastMousePos = Vector2f(event.mouseMove.x,event.mouseMove.y);
                break;}
            case sf::Event::MouseEntered:{break;}
            case sf::Event::MouseLeft:{break;}
            case sf::Event::JoystickButtonPressed:{break;}
            case sf::Event::JoystickButtonReleased:{break;}
            case sf::Event::JoystickMoved:{break;}
            case sf::Event::JoystickConnected:{break;}
            case sf::Event::JoystickDisconnected:{break;}
            case sf::Event::TouchBegan:{break;}
            case sf::Event::TouchMoved:{break;}
            case sf::Event::TouchEnded:{break;}
            case sf::Event::SensorChanged:{break;}

            case sf::Event::Count:{break;}
            default:{break;}

        }

    }
}

const vector<sf::Event> &PixelDisplay::getLastEvents() const
{
    return m_lastEventList;
}
void PixelDisplay::zoomViewAt(sf::Vector2i pixel, float zoom)
{
    const sf::Vector2f beforeCoord{ m_renderWindow->mapPixelToCoords(pixel) };
    m_view = m_renderWindow->getView();
    m_viewPortZoom *= zoom;
    m_view.zoom(zoom);
    m_renderWindow->setView(m_view);
    const sf::Vector2f afterCoord{ m_renderWindow->mapPixelToCoords(pixel) };
    const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
    m_view.move(offsetCoords);
    m_renderWindow->setView(m_view);
    updateRenderFrame();
}
void PixelDisplay::updateRenderFrame()
{
    m_view = m_renderWindow->getView();
    m_renderFrame.setPos(m_view.getCenter()-m_view.getSize()/2.f);
    m_renderFrame.setSize(m_view.getSize());
}
void PixelDisplay::setView(const RectF &frame)
{
    m_view = m_renderWindow->getView();
    m_view.reset(sf::FloatRect(frame.getPos(),frame.getSize()));
    m_view.setCenter(frame.getPos().x + frame.getSize().x/2,frame.getPos().y + frame.getSize().y/2);
    m_viewPortZoom = frame.getSize().x / m_renderFrame.getSize().x;
    m_renderWindow->setView(m_view);
    updateRenderFrame();
}
void PixelDisplay::setCameraZoom(float zoom)
{
    m_view = m_renderWindow->getView();
    if(m_viewPortZoom <= 0)
    {
        m_view.reset(sf::FloatRect(m_renderFrame.getPos(),m_renderFrame.getSize()));
        m_viewPortZoom = 1;
    }
    m_view.zoom(zoom/m_viewPortZoom);
    m_viewPortZoom = zoom;
    m_renderWindow->setView(m_view);
    updateRenderFrame();
}
void PixelDisplay::setCameraPos(const Vector2f &pos)
{
    m_view = m_renderWindow->getView();
    m_view.setCenter(pos);
    m_renderWindow->setView(m_view);
    updateRenderFrame();
}


const Vector2u &PixelDisplay::getWindowSize() const
{
    return m_windowSize;
}
const Vector2u &PixelDisplay::getMapSize() const
{
    return m_pixelMapSize;
}
RenderWindow *PixelDisplay::getRenderWindow()
{
    return m_renderWindow;
}
const RectF &PixelDisplay::getRenderFrame() const
{
    return m_renderFrame;
}
const DisplayStats &PixelDisplay::getStats() const
{
    return m_stats;
}


void PixelDisplay::subscribePainter(Painter *painter)
{
    if(painter->getRenderLayer() >= m_maxRenderLayers)
        painter->setRenderLayer(m_maxRenderLayers-1);

    painter->subscribe_painterSignal(this);
    if(painter->isVisible())
    {
        size_t layer = painter->getRenderLayer();
        m_renderLayerList[layer].table.insert({painter,painter});

        // Update stats
        m_stats.avtivePaintersInLayer[layer] = m_renderLayerList[layer].table.size();
        m_stats.activePainters = 0;
        for(size_t i=0; i<m_renderLayerList.size(); i++)
            m_stats.activePainters += m_renderLayerList[i].table.size();
    }
}
void PixelDisplay::unsubscribePainter(Painter *painter)
{
    m_stats.activePainters = 0;
    for(size_t i=0; i<m_renderLayerList.size();  i++)
    {
        m_renderLayerList[i].table.erase(painter);

        // Update stats
        m_stats.avtivePaintersInLayer[i] = m_renderLayerList[i].table.size();
        m_stats.activePainters += m_renderLayerList[i].table.size();
    }
    painter->unsubscribe_painterSignal(this);
}
void PixelDisplay::subscribePainter(const vector<Painter *> painterList)
{
    for(auto p : painterList)
        subscribePainter(p);
}
void PixelDisplay::unsubscribePainter(const vector<Painter *> painterList)
{
    for(auto p : painterList)
        unsubscribePainter(p);
}
void PixelDisplay::renderLayerChanged(Painter *sender, size_t lastLayer, size_t &newLayer)
{
    if(newLayer >= m_maxRenderLayers)
        newLayer = m_maxRenderLayers-1;
    if(newLayer == lastLayer)
        return;
    if(sender->isVisible())
    {
        m_renderLayerList[lastLayer].table.erase(sender);
        m_renderLayerList[newLayer].table.insert({sender,sender});
    }
}
void PixelDisplay::isInvisible(Painter *sender)
{
    size_t layer = sender->getRenderLayer();
    pthread_mutex_lock(&m_mutex);
    m_renderLayerList[layer].table.erase(sender);
    m_stats.avtivePaintersInLayer[layer]--;
    m_stats.activePainters--;
    pthread_mutex_unlock(&m_mutex);
}
void PixelDisplay::isVisible(Painter *sender)
{
    size_t layer = sender->getRenderLayer();
    pthread_mutex_lock(&m_mutex);
    m_renderLayerList[layer].table.insert({sender,sender});
    m_stats.avtivePaintersInLayer[layer]++;
    m_stats.activePainters++;
    pthread_mutex_unlock(&m_mutex);
}
