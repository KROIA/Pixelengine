#include "mouseMoveEvent.h"

DisplayInterface *MouseMoveEvent::m_displayInterface = nullptr;
MouseMoveEvent::MouseMoveEvent()
{
    if(!m_displayInterface)
    {
        qDebug() << "MouseMoveEvent: DisplayInterface == nullptr ";
    }
}
MouseMoveEvent::~MouseMoveEvent()
{

}
void MouseMoveEvent::setDisplayInterface(DisplayInterface *display)
{
    m_displayInterface = display;
}

void MouseMoveEvent::checkEvent(float deltaTime)
{
   // sf::Mouse::setPosition(m_displayInterface->getWindowPos() + Vector2i(m_displayInterface->getWindowSize()/2u)+Vector2i(1,0));
    m_currentPosAbsolut = sf::Mouse::getPosition();
    if(m_currentPosAbsolut != m_lastPosAbsolut)
    {
        SIGNAL_EMIT(MouseMoveEvent,moved)
    }
    m_lastPosAbsolut = m_currentPosAbsolut;

    m_pixelPosRelative = m_currentPosAbsolut - m_displayInterface->getWindowPos();//-Vector2i(14,65); // for a Strange offset because of the titleBar of the window

    RectF renderRect    = m_displayInterface->getRenderFrame();
   // m_worldPos.x = (m_pixelPosRelative.x * renderRect.getSize().x) / windowSize.x + renderRect.getPos().x;
   // m_worldPos.y = (m_pixelPosRelative.y * renderRect.getSize().y) / windowSize.y + renderRect.getPos().y;

    m_worldPos = m_displayInterface->mapPixelToCoords(m_pixelPosRelative);

    //qDebug() << "MousePos abs: "<<m_lastPosAbsolut.x <<" "<<m_lastPosAbsolut.y<<"\tReltative:"<<m_pixelPosRelative.x <<" "<<m_pixelPosRelative.y<<"\tWorldPos: "<<m_worldPos.x <<" "<<m_worldPos.y;
}
Vector2i MouseMoveEvent::getPixelPos() const
{
    return m_currentPosAbsolut;
}
Vector2i MouseMoveEvent::getPixelPosRelative() const
{
    return m_pixelPosRelative;
}
Vector2f MouseMoveEvent::getPos() const
{
    return m_worldPos;
}

