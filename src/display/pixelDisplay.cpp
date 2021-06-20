#include "pixelDisplay.h"

PixelDisplay::PixelDisplay(const PointU &windowSize, const PointU &pixelSize)
{
    m_windowSize = windowSize;
    m_pixelMapSize  = pixelSize;
    m_renderWindow = new sf::RenderWindow(sf::VideoMode(m_windowSize.getX(),m_windowSize.getY()),
                                          "PixelDisplay");

    m_windowView = m_renderWindow->getView();
    m_clearColor = Color(50,50,50);


    m_image.create(m_pixelMapSize.getX(),m_pixelMapSize.getY(),m_clearColor);
    m_texture.loadFromImage(m_image);
    m_sprite.setTexture(m_texture);
    m_sprite.setScale((double)windowSize.getX()/(double)pixelSize.getX(),
                      (double)windowSize.getY()/(double)pixelSize.getY());

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

    m_renderWindow->clear();
    m_texture.loadFromImage(m_image);
    m_renderWindow->draw(m_sprite);
    for(DisplayText* &text : m_textList)
    {
        if(text == nullptr)
            continue;
        if(text->isVisible())
        {
            m_renderWindow->draw(text->getText());
        }
    }

    m_renderWindow->display();
    clear();
}
void PixelDisplay::clear()
{
    auto px1 = reinterpret_cast<sf::Color*>(const_cast<sf::Uint8*>(m_image.getPixelsPtr()));
    std::fill(px1, px1 + m_image.getSize().x * m_image.getSize().y, m_clearColor);
}

void PixelDisplay::setPixel(const PointU &pos, const Color &color)
{
    if(pos.getX() >= m_pixelMapSize.getX() || pos.getY() >= m_pixelMapSize.getY())
        return;
    m_image.setPixel(pos.getX(),pos.getY(),color);
}
void PixelDisplay::setPixel(const Pixel &pixel)
{
    if(unsigned(pixel.getX()) >= m_pixelMapSize.getX() || unsigned(pixel.getY()) >= m_pixelMapSize.getY())
        return;
    m_image.setPixel(pixel.getX(),pixel.getY(),pixel);
}
void PixelDisplay::setPixel(const vector<Pixel> &pixelList)
{
    for(size_t i=0; i<pixelList.size(); i++)
    {
        this->setPixel(pixelList[i]);
    }
}
bool PixelDisplay::isOpen() const
{
    return m_renderWindow->isOpen();
}

sf::Event PixelDisplay::handleEvents()
{
    KeyEvent e;
    e.callbackFunction = nullptr;
   return this->handleEvents(e);
}
sf::Event PixelDisplay::handleEvents(const KeyEvent &eventHandler)
{
    vector<KeyEvent> eh{eventHandler};
    return this->handleEvents(eh);
}
sf::Event PixelDisplay::handleEvents(const vector<KeyEvent> &eventHandlerList)
{
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
                m_windowView.setSize(m_windowSize.getX(),m_windowSize.getY());

                m_renderWindow->setView(m_windowView);
                sf::Vector2u size(m_windowSize.getX(),m_windowSize.getY());
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
    for(size_t i=0; i<eventHandlerList.size(); i++)
    {
        if(eventHandlerList[i].callbackFunction == nullptr)
            continue;
        if(sf::Keyboard::isKeyPressed(eventHandlerList[i].key))
        {
            (eventHandlerList[i].callbackFunction)();
        }
    }
    return event;
}

/*bool PixelDisplay::loadFontFromFile(const std::string& filename)
{
    bool ret = m_font.loadFromFile(filename);
    if (!ret)
    {
        qDebug()  << "can't load font";
    }
    else
    {
        for(Text* &listedText : m_textList)
        {
            listedText->text.setFont(m_font);
        }
    }
    return ret;
}*/
bool PixelDisplay::addText(DisplayText *text)       // This function will not own the Text Object!
{
    for(DisplayText* &listedText : m_textList)
    {
        if(listedText == text)
            return true;
        if(text == nullptr)
            return false;
    }
    //text->setFont(m_font);
    if(m_pixelMapSize.getX() != 0)
        text->setPixelRatio(double(m_windowSize.getX()) / double(m_pixelMapSize.getX()));
    m_textList.push_back(text);
    return true;
}
bool PixelDisplay::removeText(DisplayText *text)
{
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
    m_textList.clear();
}
PointU PixelDisplay::getWindowSize() const
{
    return m_windowSize;
}
PointU PixelDisplay::getMapSize() const
{
    return m_pixelMapSize;
}
