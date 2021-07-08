#include "pixelDisplay.h"

PixelDisplay::PixelDisplay(const Vector2u &windowSize, const Vector2u &pixelSize)
{
    m_windowSize    = windowSize;
    m_pixelMapSize  = pixelSize;
    m_dragMap = false;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    m_renderWindow = new sf::RenderWindow(sf::VideoMode(m_windowSize.x,m_windowSize.y),
                                          "PixelDisplay",sf::Style::Default, settings);

    m_clearColor = Color(0,0,0);


    m_image.create(m_pixelMapSize.x,m_pixelMapSize.y,m_clearColor);
    m_texture.loadFromImage(m_image);
    m_sprite.setTexture(m_texture);

    //setRenderFrame(RectF(Vector2f(0,0),Vector2f(m_pixelMapSize)));

    m_localPixlerUsed = true;
    m_spriteListUsed  = true;
    m_vertexPathUsed  = true;
    m_textListUsed    = false;
    m_stats_renderSprites = 0;
    m_stats_renderText    = 0;
    m_stats_renderVertexPaths = 0;
    m_viewPortZoom = 1;

    float zoomFac = (float)pixelSize.x / (float)windowSize.x;
    zoomViewAt(Vector2i(0,0),zoomFac);
    //this->setView(RectF(0,0,float(m_pixelMapSize.x),float(m_pixelMapSize.y)));
    clear();
}
PixelDisplay::PixelDisplay(const PixelDisplay &other)
{
     this->m_windowSize   = other.m_windowSize;
     this->m_pixelMapSize    = other.m_pixelMapSize;
     this->m_renderWindow = other.m_renderWindow;
     this->m_texture      = other.m_texture;
     this->m_image        = other.m_image;
     this->m_sprite       = other.m_sprite;
     this->m_clearColor   = other.m_clearColor;
}
PixelDisplay::~PixelDisplay()
{
    m_renderWindow->close();
    delete m_renderWindow;
}

void PixelDisplay::display()
{
    EASY_FUNCTION("PixelDisplay::display()",profiler::colors::Blue);

    m_renderWindow->clear();
    m_stats_renderVertexPaths = m_vertexPathList.size();
    m_stats_renderSprites     = m_spriteList.size();

    EASY_BLOCK("local pixler",profiler::colors::Blue100);
    if(m_localPixlerUsed)
    {
        m_texture.loadFromImage(m_image);
        m_renderWindow->draw(m_sprite);
    }
    EASY_END_BLOCK;
    EASY_BLOCK("draw m_spriteList",profiler::colors::Blue100);
    if(m_spriteListUsed)
    {
        for(Sprite* &object : m_spriteList)
        {
            m_renderWindow->draw(*object);

        }
    }
    EASY_END_BLOCK;
    /*
    m_spriteListUsed = true;
    m_spriteList.push_back(sprite);
    m_spriteList[m_spriteList.size()-1].setScale(m_renderScale.x,m_renderScale.y);
    Vector2f point = sprite.getPosition() + m_globalDisplayFrame.getPos();
    m_spriteList[m_spriteList.size()-1].setPosition(point.x * m_renderScale.x, point.y * m_renderScale.y);
     */
    EASY_BLOCK("draw m_spriteSubscriberList",profiler::colors::Blue100);
    //Vector2f displayFramePos = m_globalDisplayFrame.getPos();
    for(Sprite* &object : m_spriteSubscriberList)
    {
        Vector2f oldPos = object->getPosition();
        Vector2f oldScale = object->getScale();
        //object->setScale(m_renderScale);

        //Vector2f newPos(displayFramePos + oldPos);
        //newPos.x *= m_renderScale.x;
        //newPos.y *= m_renderScale.y;
        //object->setPosition(newPos);

        m_renderWindow->draw(*object);
        object->setScale(oldScale);
        object->setPosition(oldPos);
    }
    EASY_END_BLOCK;

    EASY_BLOCK("draw m_vertexPathList",profiler::colors::Blue100);
    if(m_vertexPathUsed)
    {
        for(size_t i=0; i<m_vertexPathList.size(); i++)
        {
            m_renderWindow->draw(m_vertexPathList[i]->line, m_vertexPathList[i]->length, m_vertexPathList[i]->type);
        }
    }
    EASY_END_BLOCK;
    EASY_BLOCK("draw m_textList",profiler::colors::Blue100);
    if(m_textListUsed)
    {
        m_stats_renderText = 0;
        for(size_t i=0; i<m_textList.size(); i++)
        {
            if(m_textList[i] == nullptr)
                continue;
            DisplayText text = *m_textList[i];

            if(text.isVisible())
            {
                m_stats_renderText++;

                if(text.getPositionFix())
                {
                    m_view = m_renderWindow->getView();
                    Vector2f textPos = m_view.getCenter()-m_view.getSize()/2.f + text.getPos()*m_viewPortZoom;
                    //textPos.y += m_viewPortZoom;

                    text.setPos(textPos);

                  //  qDebug() << "textPos : "<<textPos.x   <<" "<<textPos.y<< " zoom: "<<m_viewPortZoom;
                    //text.setCharacterSize(round(text.getCharacterSize()*m_viewPortZoom));
                    sf::Text t = text.getText();
                    t.setScale(m_viewPortZoom,m_viewPortZoom);
                    m_renderWindow->draw(t);
                }
                else
                {
                   /* sf::Text t = text.getText();
                    t.setScale(1/m_viewPortZoom,1/m_viewPortZoom);
                    m_renderWindow->draw(t);*/
                    m_renderWindow->draw(text.getText());

                }
                //text.setPixelRatio(m_renderScale.x);
               // text.move(m_globalDisplayFrame.getPos());



            }
        }
    }
    EASY_END_BLOCK;
    EASY_BLOCK("m_renderWindow->display()",profiler::colors::Blue100);
    m_renderWindow->display();
    EASY_END_BLOCK;
    clear();
}
void PixelDisplay::clear()
{
    EASY_FUNCTION(profiler::colors::Blue100);
    if(m_localPixlerUsed)
    {
        auto px1 = reinterpret_cast<sf::Color*>(const_cast<sf::Uint8*>(m_image.getPixelsPtr()));
        std::fill(px1, px1 + m_image.getSize().x * m_image.getSize().y, m_clearColor);
        m_localPixlerUsed = false;
    }
    if(m_spriteListUsed)
    {
        m_spriteListUsed = false;
        clearSprite();
    }
    if(m_vertexPathUsed)
    {
        m_vertexPathUsed = false;
        clearVertexLine();
    }

}

void PixelDisplay::setPixel(const Vector2i &pos, const Color &color)
{
    EASY_FUNCTION(profiler::colors::Blue200);
    if(pos.x < 0 || pos.y < 0)
        return;
    if(unsigned(pos.x) >= m_pixelMapSize.x || unsigned(pos.y) >= m_pixelMapSize.y)
        return;
    EASY_BLOCK("m_image.setPixel",profiler::colors::Blue300);
    m_image.setPixel(pos.x,pos.y,color);
    m_localPixlerUsed = true;

}
void PixelDisplay::setPixel(const Pixel &pixel)
{
    EASY_FUNCTION(profiler::colors::Blue300);
    int x = pixel.getX();
    int y = pixel.getY();
    if(x < 0 || y < 0)
        return;
    if(unsigned(x) >= m_pixelMapSize.x || unsigned(y) >= m_pixelMapSize.y)
        return;
    EASY_BLOCK("m_image.setPixel",profiler::colors::Blue300);
    m_image.setPixel(x,y,pixel);
    m_localPixlerUsed = true;
}
void PixelDisplay::setPixel(const vector<Pixel> &pixelList)
{
    EASY_FUNCTION(profiler::colors::Blue400);
    for(size_t i=0; i<pixelList.size(); i++)
    {
        this->setPixel(pixelList[i]);
    }
}

void PixelDisplay::clearSprite()
{
    size_t lastSize = m_spriteList.size();
    m_spriteList.clear();
    m_spriteList.reserve(lastSize);
}
void PixelDisplay::addSprite(Sprite *sprite)
{
    EASY_FUNCTION(profiler::colors::Blue400);
    m_spriteListUsed = true;
    m_spriteList.push_back(sprite);
    //m_spriteList[m_spriteList.size()-1].setScale(m_renderScale.x,m_renderScale.y);
    //Vector2f point = sprite.getPosition() + m_globalDisplayFrame.getPos();
    //m_spriteList[m_spriteList.size()-1].setPosition(point.x * m_renderScale.x, point.y * m_renderScale.y);
}
void PixelDisplay::subscribeSprite(Sprite *sprite)
{
    m_spriteSubscriberList.push_back(sprite);
}
void PixelDisplay::unsubscribeSprite(Sprite *sprite)
{
    for(size_t i=0; i<m_spriteSubscriberList.size(); i++)
        if(m_spriteSubscriberList[i] == sprite)
            m_spriteSubscriberList.erase(m_spriteSubscriberList.begin()+i);
}
void PixelDisplay::clearVertexLine()
{
    for(size_t i=0; i<m_vertexPathList.size(); i++)
        delete m_vertexPathList[i];
    m_vertexPathList.clear();
    m_vertexPathList.reserve(500);
}
void PixelDisplay::addVertexLine(VertexPath* path)
{
    m_vertexPathUsed = true;
    if(path->line != nullptr && path->length > 0)
        m_vertexPathList.push_back(path);

  /*  m_vertexPathList[m_vertexPathList.size()-1]->move(m_globalDisplayFrame.getPos());
    for(size_t i=0; i<m_vertexPathList[m_vertexPathList.size()-1]->length; i++)
    {

        m_vertexPathList[m_vertexPathList.size()-1]->line[i].position.x *= m_renderScale.x;
        m_vertexPathList[m_vertexPathList.size()-1]->line[i].position.y *= m_renderScale.y;
    }*/
}
void PixelDisplay::addVertexLine(const vector<VertexPath*> &pathList)
{
    m_vertexPathList.reserve(m_vertexPathList.size()+pathList.size());
    for(VertexPath* path : pathList)
    {
        addVertexLine(path);
    }
}

bool PixelDisplay::isOpen() const
{
    return m_renderWindow->isOpen();
}

void PixelDisplay::handleEvents()
{
    EASY_FUNCTION(profiler::colors::Blue500);
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
               /* sf::View view = m_renderWindow->getView();
                view.setSize(m_windowSize.x,m_windowSize.y);

                m_renderWindow->setView(view);*/
                m_renderWindow->setSize(m_windowSize);
                m_renderWindow->setView(m_view);
                /*RectF oldFrame = m_renderFrame;
                updateRenderFrame();
                setView(oldFrame);*/
                break;
            }
            case sf::Event::LostFocus:{break;}
            case sf::Event::GainedFocus:{break;}
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
void PixelDisplay::handleEvents(const KeyEvent &eventHandler)
{
    EASY_FUNCTION(profiler::colors::Blue600);
    if(eventHandler.callbackFunction == nullptr)
        return;
    if(sf::Keyboard::isKeyPressed(eventHandler.key))
    {
        (eventHandler.callbackFunction)();
    }
}
void PixelDisplay::handleEvents(const vector<KeyEvent> &eventHandlerList)
{
    EASY_FUNCTION(profiler::colors::Blue700);
    EASY_BLOCK("for(size_t i=0; i<eventHandlerList.size(); i++)",profiler::colors::Blue700);
    for(size_t i=0; i<eventHandlerList.size(); i++)
    {
        if(eventHandlerList[i].callbackFunction == nullptr)
            continue;
        if(sf::Keyboard::isKeyPressed(eventHandlerList[i].key))
        {
            (eventHandlerList[i].callbackFunction)();
        }
    }
    EASY_END_BLOCK;
   // return event;
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
    m_view.setViewport(sf::FloatRect(frame.getPos(),frame.getSize()));
    m_viewPortZoom = frame.getSize().x / m_renderFrame.getSize().x;
    m_renderWindow->setView(m_view);
    updateRenderFrame();
}

bool PixelDisplay::addText(DisplayText *text)       // This function will not own the Text Object!
{
    EASY_FUNCTION(profiler::colors::Blue800);
    for(DisplayText* &listedText : m_textList)
    {
        if(listedText == text)
            return true;
        if(text == nullptr)
            return false;
    }
    //text->setFont(m_font);
    /*if(m_pixelMapSize.x != 0)
        text->setPixelRatio(float(m_windowSize.x) / float(m_pixelMapSize.x));*/
    m_textList.push_back(text);
    m_textListUsed = true;
    return true;
}
bool PixelDisplay::removeText(DisplayText *text)
{
    EASY_FUNCTION(profiler::colors::Blue900);
    for(size_t i=0; i<m_textList.size(); i++)
    {
        if(m_textList[i] == text)
        {
            m_textList.erase(m_textList.begin()+i);
            return true;
        }
    }
    if(m_textList.size() == 0)
        m_textListUsed = false;
    return false;
}
void PixelDisplay::clearText()
{
    EASY_FUNCTION(profiler::colors::BlueA100);
    m_textList.clear();
    m_textListUsed = false;
}
Vector2u PixelDisplay::getWindowSize() const
{
    return m_windowSize;
}
Vector2u PixelDisplay::getMapSize() const
{
    return m_pixelMapSize;
}
RenderWindow *PixelDisplay::getRenderWindow()
{
    return m_renderWindow;
}
/*Vector2f PixelDisplay::getRenderScale()
{
    return m_renderScale;
}
void PixelDisplay::setRenderFramePosCenter(const Vector2f &pos)
{
    Vector2f size = m_globalDisplayFrame.getSize() / 2.f;
    setRenderFramePos(size - pos);
}
void PixelDisplay::setRenderFramePos(const Vector2f &pos)
{
    m_globalDisplayFrame.setPos(pos);
}
void PixelDisplay::moveRenderFrame(const Vector2f &vec)
{
    m_globalDisplayFrame.move(vec);
}*/
/*void PixelDisplay::setRenderFrame(const RectF &frame)
{
    m_globalDisplayFrame = frame;
    m_renderScale.x = (float)m_windowSize.x/m_globalDisplayFrame.getSize().x;
    m_renderScale.y = (float)m_windowSize.y/m_globalDisplayFrame.getSize().y;

    m_sprite.setScale(m_renderScale);
    qDebug() << "getPos       : "<<m_globalDisplayFrame.getPos().x<< " "<<m_globalDisplayFrame.getPos().y;
    qDebug() << "m_renderScale: "<<m_renderScale.x<< " "<<m_renderScale.y;
   // m_windowView.setViewport(sf::FloatRect(m_globalDisplayFrame.getPos().x, m_globalDisplayFrame.getPos().y, m_globalDisplayFrame.getSize().x, m_globalDisplayFrame.getSize().y));

}*/
const RectF PixelDisplay::getRenderFrame() const
{

    //rect.setSize(Vector::multiply(viewport.getSize(),Vector2f(m_windowSize)));
    //qDebug() << viewport.getPosition().x<< " "<<viewport.getPosition().y << " "<<viewport.getSize().x<<" "<<viewport.getSize().y;
    return m_renderFrame;
}
unsigned long long PixelDisplay::stats_getRenderSprites() const
{
    return m_stats_renderSprites;
}
unsigned long long PixelDisplay::stats_getRenderVertexPaths() const
{
    return m_stats_renderVertexPaths;
}
unsigned long long PixelDisplay::stats_getRenderText() const
{
    return m_stats_renderText;
}
