#include "painterGroup.h"

PainterGroup::PainterGroup()
    :   Group<GameObject *>()
{
    this->setVisibility(true);
}
PainterGroup::PainterGroup(const PainterGroup &other)
    :   Group<GameObject *>(other)
{
    this->m_isVisible = other.m_isVisible;
}

PainterGroup::~PainterGroup()
{

}

void PainterGroup::setVisibility(const bool &isVisible)
{
    m_isVisible = isVisible;
    for(size_t i=0; i<m_objectList.size(); i++)
    {
        m_objectList[i]->setVisibility(isVisible);
    }
}
const bool &PainterGroup::isVisible() const
{
    return m_isVisible;
}
