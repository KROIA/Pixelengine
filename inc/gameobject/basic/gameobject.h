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
        virtual void preRun();
        virtual void tick(const Vector2i&direction);
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

        virtual void setPos(int x, int y);
        virtual void setPos(const Vector2i &pos);
        virtual void setPos(float x, float y);
        virtual void setPos(const Vector2f &pos);

        virtual void setX(int x);
        virtual void setY(int y);
        virtual void setX(float x);
        virtual void setY(float y);

        virtual void moveToPos(const Vector2i&destination,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void moveToPos(const int &x,const int &y,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void move(const Vector2i&vec,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void move(const Vector2f &vec,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void move(const float &deltaX, const float &deltaY,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void moveX(const float &delta,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void moveY(const float &delta,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual const Vector2f &getPos() const;
        virtual const Vector2f &getMovingVector() const;

        virtual float getRotation() const;
        virtual void setRotation(const float &deg);
        virtual void rotate_90();
        virtual void rotate_180();
        virtual void rotate_270();
        virtual void setRotation(const Vector2f &rotationPoint,const float &deg);
        virtual void rotate_90(const Vector2f &rotationPoint);
        virtual void rotate_180(const Vector2f &rotationPoint);
        virtual void rotate_270(const Vector2f &rotationPoint);



        // Collider settings
        virtual void addHitbox(const RectI &box);
        virtual void addHitbox(const vector<RectI> &boxList);
        virtual void eraseHitbox(const size_t &index);
        virtual void clearCollider();
        virtual const bool &isBoundingBoxUpdated() const;
        virtual void updateBoundingBox();
    //    virtual void setHitboxFromTexture();
        virtual void setHitboxFromTexture(const Texture &texture);
        virtual void setHitboxVisibility(const bool &isVisible);
        virtual void showBoundingBox(bool enable);
        virtual void updateHitboxPainter();
        virtual const bool &isHitboxVisible() const;
        //virtual bool checkTextureUpdateForCollider();

        // Painter settings
     //   virtual void reservePixelAmount(const size_t amount);
     //   virtual void addPixel(const Pixel &pixel);
     //   virtual void addPixel(const vector<Pixel> &pixelList);
     //   virtual const Pixel &getPixel(const size_t &index) const;
     //   virtual const Pixel &getPixel(const Vector2i&pixelPos) const;
     //   virtual const Pixel &getPixel(int x, int y) const;
     //   virtual size_t getPixelAmount() const;
     //   virtual void setPixelColor(const size_t &index, const Color &color);
     //   virtual void setPixelColor(const Vector2i&pixelPos, const Color &color);
     //   virtual void setPixelColor(int x, int y, const Color &color);
     //   virtual void setPixelColor(const Color &color);
     //   virtual void erasePixel(const size_t &index);
     //   virtual void erasePixel(const Vector2i&pixelPos);
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
        Collider      *m_collider;
        Painter       *m_painter;
        PixelPainter  *m_hitboxPainter;
        bool          m_boundingBoxIsVisible;

        bool          m_textureIsActiveForCollider;

        vector<DisplayText* > m_displayTextList;

        unsigned int m_rotationDeg;

    private:

        void rotate(const float &deg);



};
#endif // GAMEOBJECT_H
