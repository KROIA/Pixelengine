#include "mouseMoveController.h"

MouseMoveController::MouseMoveController()
    :   Controller()
{
    m_mouseMoveEvent        =   new MouseMoveEvent();
    this->setClipToCoursor(false);
    this->setDeltaFactor(2);

    Controller::addEvent(m_mouseMoveEvent);
}
MouseMoveController::MouseMoveController(const MouseMoveController &other)
    :   Controller(other)
{
    m_mouseMoveEvent        =   new MouseMoveEvent();
    this->m_clipToCoursor   =   other.m_clipToCoursor;
    this->setDeltaFactor(2);

    Controller::addEvent(m_mouseMoveEvent);
}
MouseMoveController::~MouseMoveController()
{
    delete m_mouseMoveEvent;
}
const MouseMoveController &MouseMoveController::operator=(const MouseMoveController &other)
{
    Controller::operator=(other);
    this->m_clipToCoursor   =   other.m_clipToCoursor;
    this->m_dumpingFactor   =   other.m_dumpingFactor;
    return *this;
}

void MouseMoveController::checkEvent(float deltaTime)
{
    Controller::checkEvent(deltaTime);
    if(!m_clipToCoursor)
    {
        Vector2f deltaPos = m_mouseMoveEvent->getPos()  - m_pos;
        float movingLength = m_stepSize + m_dumpingFactor*Vector::length(deltaPos);
        if(Vector::length(deltaPos) > 0.1)
        {
            float movingAngle;
            if(deltaPos.y == 0)
            {
                if(deltaPos.x > 0)
                    movingAngle = 0;
                else
                    movingAngle = M_PI;
            }
            else
            {
                movingAngle = asin(deltaPos.y/Vector::length(deltaPos));
                if(deltaPos.x < 0)
                    movingAngle = M_PI-movingAngle;
            }
            Vector2f deltaMove(cos(movingAngle) * movingLength, sin(movingAngle) * movingLength);
            Controller::move(deltaMove);
           // qDebug()<<"move: "<<deltaMove.x<<" "<<deltaMove.y<<" angle:"<<movingAngle*180.f/M_PI<<"\tdelta:"<<deltaPos.x<<" "<<deltaPos.y;
        }
    }
}

void MouseMoveController::setClipToCoursor(bool enable)
{
    m_clipToCoursor = enable;
    if(m_clipToCoursor)
    {
        SIGNAL_SUBSCRIBE(MouseMoveEvent,m_mouseMoveEvent)
        Controller::useTimescale(false);
    }
    else
    {
        SIGNAL_UNSUBSCRIBE(MouseMoveEvent,m_mouseMoveEvent)
        Controller::useTimescale(true);
    }
}
bool MouseMoveController::getClipToCoursor() const
{
    return m_clipToCoursor;
}
void MouseMoveController::setDeltaFactor(float factor)
{
    m_dumpingFactor = factor;
}
bool MouseMoveController::getDeltaFactor() const
{
    return m_dumpingFactor;
}
void MouseMoveController::setRotation(float deg)
{
    // norotation for this controller
}
void MouseMoveController::rotate(float deg)
{}
void MouseMoveController::rotate_90()
{}
void MouseMoveController::rotate_180()
{}
void MouseMoveController::rotate_270()
{}

SLOT_DEFINITION(MouseMoveController,MouseMoveEvent,moved)
{
    Controller::moveToPos(m_mouseMoveEvent->getPos());
}
