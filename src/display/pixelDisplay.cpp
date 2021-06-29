#include "pixelDisplay.h"

PixelDisplay::PixelDisplay(const Vector2u &windowSize, const Vector2u &pixelSize)
{
    m_windowSize    = windowSize;
    m_pixelMapSize  = pixelSize;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    m_renderWindow = new sf::RenderWindow(sf::VideoMode(m_windowSize.x,m_windowSize.y),
                                          "PixelDisplay",sf::Style::Default, settings);

    m_windowView = m_renderWindow->getView();
    m_clearColor = Color(50,50,50);

    m_spriteScale.x = (float)m_windowSize.x/(float)m_pixelMapSize.x;
    m_spriteScale.y = (float)m_windowSize.y/(float)m_pixelMapSize.y;

    m_image.create(m_pixelMapSize.x,m_pixelMapSize.y,m_clearColor);
    m_texture.loadFromImage(m_image);
    m_sprite.setTexture(m_texture);
    m_sprite.setScale(m_spriteScale);
}
PixelDisplay::PixelDisplay(const PixelDisplay &other)
{
     this->m_windowSize   = other.m_windowSize;
     this->m_pixelMapSize    = other.m_pixelMapSize;
     this->m_renderWindow = other.m_renderWindow;
     this->m_windowView   = other.m_windowView;
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
    //auto stats_timePoint_1 = std::chrono::system_clock::now();

    m_renderWindow->clear();
    //m_texture.loadFromImage(m_image);
    //m_renderWindow->draw(m_sprite);

    EASY_BLOCK("draw m_spriteList",profiler::colors::Blue100);
    for(Sprite &object : m_spriteList)
    {
        m_renderWindow->draw(object);
    }
    EASY_END_BLOCK;
    EASY_BLOCK("draw m_textList",profiler::colors::Blue100);
    for(DisplayText* &text : m_textList)
    {
        if(text == nullptr)
            continue;
        if(text->isVisible())
        {
            m_renderWindow->draw(text->getText());
        }
    }
    EASY_END_BLOCK;
    EASY_BLOCK("draw m_vertexPathList",profiler::colors::Blue100);
    for(size_t i=0; i<m_vertexPathList.size(); i++)
        m_renderWindow->draw(m_vertexPathList[i].line, m_vertexPathList[i].length, m_vertexPathList[i].type);
    EASY_END_BLOCK;
    EASY_BLOCK("m_renderWindow->display()",profiler::colors::Blue100);
    m_renderWindow->display();
    EASY_END_BLOCK;
    clear();
}
void PixelDisplay::clear()
{
    EASY_FUNCTION(profiler::colors::Blue100);
    auto px1 = reinterpret_cast<sf::Color*>(const_cast<sf::Uint8*>(m_image.getPixelsPtr()));
    std::fill(px1, px1 + m_image.getSize().x * m_image.getSize().y, m_clearColor);
    clearSprite();
    clearVertexLine();
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
    m_spriteList.clear();
    m_spriteList.reserve(500);
}
void PixelDisplay::addSprite(Sprite &sprite)
{
    m_spriteList.push_back(sprite);
    m_spriteList[m_spriteList.size()-1].setScale(m_spriteScale.x,m_spriteScale.y);
    Vector2f point(sprite.getPosition().x,sprite.getPosition().y);
    m_spriteList[m_spriteList.size()-1].setPosition(point.x * m_spriteScale.x, point.y * m_spriteScale.y);
}
void PixelDisplay::clearVertexLine()
{
    for(size_t i=0; i<m_vertexPathList.size(); i++)
        delete m_vertexPathList[i].line;
    m_vertexPathList.clear();
    m_vertexPathList.reserve(500);
}
void PixelDisplay::addVertexLine(VertexPath path)
{
    if(path.line != nullptr && path.length > 0)
        m_vertexPathList.push_back(path);

    for(size_t i=0; i<m_vertexPathList[m_vertexPathList.size()-1].length; i++)
    {
        m_vertexPathList[m_vertexPathList.size()-1].line[i].position.x *= m_spriteScale.x;
        m_vertexPathList[m_vertexPathList.size()-1].line[i].position.y *= m_spriteScale.y;
    }
}

bool PixelDisplay::isOpen() const
{
    return m_renderWindow->isOpen();
}

sf::Event PixelDisplay::handleEvents()
{
    EASY_FUNCTION(profiler::colors::Blue500);
    KeyEvent e;
    e.callbackFunction = nullptr;
   return this->handleEvents(e);
}
sf::Event PixelDisplay::handleEvents(const KeyEvent &eventHandler)
{
    EASY_FUNCTION(profiler::colors::Blue600);
    vector<KeyEvent> eh{eventHandler};
    return this->handleEvents(eh);
}
sf::Event PixelDisplay::handleEvents(const vector<KeyEvent> &eventHandlerList)
{
    EASY_FUNCTION(profiler::colors::Blue700);
    sf::Event event;
    event.type = sf::Event::EventType::Count;
    if(!m_renderWindow->isOpen())
    {
        return event;
    }

    while(m_renderWindow->pollEvent(event))
    {

        switch(event.type)
        {
            case sf::Event::Closed:
            {
                m_renderWindow->close();
                break;
            }
            case sf::Event::Resized:
            {
                m_windowView.setSize(m_windowSize.x,m_windowSize.y);

                m_renderWindow->setView(m_windowView);
                sf::Vector2u size(m_windowSize.x,m_windowSize.y);
                m_renderWindow->setSize(size);
                break;
            }
            case sf::Event::LostFocus:{break;}
            case sf::Event::GainedFocus:{break;}
            case sf::Event::TextEntered:{break;}
            case sf::Event::KeyPressed:{break;}
            case sf::Event::KeyReleased:{break;}
            case sf::Event::MouseWheelMoved:{break;}
            case sf::Event::MouseWheelScrolled:{break;}
            case sf::Event::MouseButtonPressed:{break;}
            case sf::Event::MouseButtonReleased:{break;}
            case sf::Event::MouseMoved:{break;}
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
    return event;
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
    if(m_pixelMapSize.x != 0)
        text->setPixelRatio(float(m_windowSize.x) / float(m_pixelMapSize.x));
    m_textList.push_back(text);
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
    return false;
}
void PixelDisplay::clearText()
{
    EASY_FUNCTION(profiler::colors::BlueA100);
    m_textList.clear();
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
Vector2f PixelDisplay::getRenderScale()
{
    return m_spriteScale;
}
