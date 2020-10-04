#include "pixelDisplay.h"

PixelDisplay::PixelDisplay(const PointU &windowSize, const PointU &pixelSize)
{
    m_windowSize = windowSize;
    m_pixelSize  = pixelSize;
    m_renderWindow = new sf::RenderWindow(sf::VideoMode(m_windowSize.getX(),m_windowSize.getY()),
                                          "PixelDisplay");

    m_windowView = m_renderWindow->getView();
    m_clearColor = Color(50,50,50);


    m_image.create(m_pixelSize.getX(),m_pixelSize.getY(),m_clearColor);
    m_texture.loadFromImage(m_image);
    m_sprite.setTexture(m_texture);
    m_sprite.setScale((double)windowSize.getX()/(double)pixelSize.getX(),
                      (double)windowSize.getY()/(double)pixelSize.getY());
}
PixelDisplay::PixelDisplay(const PixelDisplay &other)
{
     this->m_windowSize   = other.m_windowSize;
     this->m_pixelSize    = other.m_pixelSize;
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
    m_texture.loadFromImage(m_image);
    //m_renderWindow->clear(m_clearColor);
    m_renderWindow->draw(m_sprite);
    m_renderWindow->display();
    clear();
}
void PixelDisplay::clear()
{
    //auto px0 = const_cast<sf::Uint8*>(m_image.getPixelsPtr());
    //std::fill(px0, px0 + m_image.getSize().x * m_image.getSize().y * 4, m_clearColor.toInteger());
    auto px1 = reinterpret_cast<sf::Color*>(const_cast<sf::Uint8*>(m_image.getPixelsPtr()));
    std::fill(px1, px1 + m_image.getSize().x * m_image.getSize().y, m_clearColor);
}

void PixelDisplay::setPixel(const PointU &pos, const Color &color)
{
    if(pos.getX() >= m_pixelSize.getX() || pos.getY() >= m_pixelSize.getY())
        return;
    m_image.setPixel(pos.getX(),pos.getY(),color);
}
void PixelDisplay::setPixel(const Pixel &pixel)
{
    if(pixel.getX() >= m_pixelSize.getX() || pixel.getY() >= m_pixelSize.getY())
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

bool PixelDisplay::handleEvents()
{
    KeyEvent e;
    e.callbackFunction = nullptr;
    return this->handleEvents(e);
}
bool PixelDisplay::handleEvents(const KeyEvent &eventHandler)
{
    vector<KeyEvent> eh{eventHandler};
    return this->handleEvents(eh);
}
bool PixelDisplay::handleEvents(const vector<KeyEvent> &eventHandlerList)
{
    if(!m_renderWindow->isOpen())
    {
        return true;
    }
    sf::Event event;
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
    return false;
}
