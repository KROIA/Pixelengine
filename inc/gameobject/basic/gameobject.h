#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "property.h"
#include "controller.h"
#include "collider.h"
#include "painter.h"
#include "hitboxPainter.h"
#include "dynamicCoordinator.h"
#include "texture.h"
#include "displayText.h"

#include "profiler.h"

class GameObjectEventHandler;
class GameObject;

class GameObject
{
    public:
        GameObject();
        GameObject(const GameObject &other);
        GameObject(Controller *controller,
                   Collider   *collider,
                   Painter    *painter);

        virtual ~GameObject();
        virtual const GameObject &operator=(const GameObject &other);

        // Events
        virtual void checkEvent();
        virtual void killMe();             // Not defined jet in the engine class
        virtual void removeMeFromEngine(); // Removes this obj from the engine, but the obj won't get destroyed
        virtual void deleteMeFromEngine(); // Removes this obj from the engine and destroyes it (delete call)


        // called by the Engine
        virtual void tick(const Point &direction);
        virtual unsigned int checkCollision(const vector<GameObject*> &other);
        virtual unsigned int checkCollision(const vector<vector<GameObject*> >&other);
        static vector<GameObject*> getCollidedObjects(GameObject *owner, Collider *collider,const vector<GameObject*> &other);
        virtual void draw(PixelDisplay &display);

        // For user call
        virtual void addController(Controller *controller);
        virtual void clearController();
        virtual void setCollider(Collider *collider);
        virtual const Collider &getCollider() const;
        virtual void setPainter(Painter *painter);
        virtual const Painter &getPainter() const;
        virtual void setEventHandler(GameObjectEventHandler *handler);

        virtual void setPos(const int &x,const int &y);
        virtual void setPos(const Point &pos);

        virtual void setX(const int &x);
        virtual void setY(const int &y);

        virtual void moveToPos(const Point &destination,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void moveToPos(const int &x,const int &y,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void move(const Vector &vec,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void move(const VectorF &vec,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void move(const double &deltaX, const double &deltaY,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void moveX(const double &delta,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void moveY(const double &delta,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual const Point getPos() const;
        virtual const VectorF      &getMovingVector() const;

        virtual double getRotation() const;
        virtual void setRotation(const double &deg);
        virtual void rotate_90();
        virtual void rotate_180();
        virtual void rotate_270();
        virtual void setRotation(const PointF &rotationPoint,const double &deg);
        virtual void rotate_90(const PointF &rotationPoint);
        virtual void rotate_180(const PointF &rotationPoint);
        virtual void rotate_270(const PointF &rotationPoint);



        // Collider settings
        virtual void addHitbox(const Rect &box);
        virtual void addHitbox(const vector<Rect> &boxList);
        virtual void eraseHitbox(const size_t &index);
        virtual void clearCollider();
        virtual const bool &isBoundingBoxUpdated() const;
        virtual void updateBoundingBox();
    //    virtual void setHitboxFromTexture();
        virtual void setHitboxFromTexture(const Texture &texture);
        virtual void setHitboxVisibility(const bool &isVisible);
        virtual void updateHitboxPainter();
        virtual const bool &isHitboxVisible() const;
        //virtual bool checkTextureUpdateForCollider();

        // Painter settings
     //   virtual void reservePixelAmount(const size_t amount);
     //   virtual void addPixel(const Pixel &pixel);
     //   virtual void addPixel(const vector<Pixel> &pixelList);
     //   virtual const Pixel &getPixel(const size_t &index) const;
     //   virtual const Pixel &getPixel(const Point &pixelPos) const;
     //   virtual const Pixel &getPixel(int x, int y) const;
     //   virtual size_t getPixelAmount() const;
     //   virtual void setPixelColor(const size_t &index, const Color &color);
     //   virtual void setPixelColor(const Point &pixelPos, const Color &color);
     //   virtual void setPixelColor(int x, int y, const Color &color);
     //   virtual void setPixelColor(const Color &color);
     //   virtual void erasePixel(const size_t &index);
     //   virtual void erasePixel(const Point &pixelPos);
     //   virtual void erasePixel(int x, int y);
     //   virtual void clearPainter(); // Deletes all pixels
        virtual void setVisibility(const bool &isVisible);
        virtual const bool &isVisible() const;
       // virtual void setTexture(Texture *texture);
       // virtual void setTexturePath(const string &path);
       // virtual void loadTexture();
       // const virtual Texture &getTexture() const;
       // virtual void setTextureOnPainter();
       // virtual void setTextureOnPainter(Texture &texture);
       // virtual bool checkTextureUpdateForPainter();

        // Properties
        virtual void setProperty(const Property::Property &property);
        virtual const Property::Property &getProperty() const;

        // Text visualisation
        virtual void addText(DisplayText *text);
        virtual void removeText(DisplayText *text);
        virtual void removeText();
        virtual void deleteText(DisplayText *text);
        virtual void deleteText();

        virtual const vector<DisplayText*> &getTextList();

    protected:
        virtual void event_hasCollision(vector<GameObject *> other);

        LayerItem m_layerItem;

        Property::Property m_property;
        GameObjectEventHandler *m_objEventHandler;

        vector<Controller*> m_controllerList;
        DynamicCoordinator m_movementCoordinator;
        Collider   *m_collider;
        Painter    *m_painter;
        PixelPainter  *m_hitboxPainter;

        //Texture    *m_texture;
        //bool        m_textureIsActiveForPainter;
        //bool        m_painterNeedsUpdateFromTexture;
        bool        m_textureIsActiveForCollider;
       // bool        m_colliderNeedsUpdateFromTexture;

        vector<DisplayText* > m_displayTextList;

        unsigned int m_rotationDeg;

    private:

        void rotate(const double &rad);


};
#endif // GAMEOBJECT_H
