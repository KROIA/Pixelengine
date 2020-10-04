#ifndef PAINTERGROUP_H
#define PAINTERGROUP_H

#include "group.h"
#include "painter.h"

class PainterGroup  :   public Group<GameObject*>
{
    public:
        PainterGroup();
        PainterGroup(const PainterGroup &other);

        virtual ~PainterGroup();

        virtual void setVisibility(const bool &isVisible);
        virtual const bool &isVisible() const;

    protected:
        bool m_isVisible;
    private:

};
#endif // PAINTERGROUP_H
