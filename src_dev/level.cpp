#include "level.h"


PixelEngine     *engine;

Player          *player;
GameObject      *obstacle1;
Wall            *wall1;
GameObject      *imported;
ManagedGameObjectGroup *objectGroup;
AnimatedTexture *animatedTexture;
GameObject      *waterBlock;
AnimatedTexture *waterTexture;
vector<AnimatedTexture *>waterTextureList;

Timer statsTimer;
Timer timer;
Timer timer2;
Timer fadeTimer;
Timer dbgTimer;
bool toggle = false;
double rad = 0;


Timer moveTimer;

Event *keyEvent_P;
Event *keyEvent_O;

// toggle Hitbox
Event *keyEvent_H;
ManagedGameObjectGroup hitboxObjectList;
bool hitboxIsVisible;


void setup_level()
{
    // Generate the engine
    unsigned int mapWidth = 300;

    //RECT dispaySize;
    //GetWindowRect(GetDesktopWindow(), &dispaySize);
    //PointU windowSize(dispaySize.right,dispaySize.bottom-60);
    double displayScale = 0.9;
    PointU windowSize(1900*displayScale,1000*displayScale);
    engine = new PixelEngine (PointU(mapWidth,double(mapWidth)*double(windowSize.getY())/double(windowSize.getX())),windowSize);
    engine->set_setting_checkEventInterval(1.0f/30.0f);
    engine->set_setting_gameTickInterval(1.0f/120.0f);
    engine->set_setting_displayInterval(1.0f/60.0f);


    // Player 2
    player = new Player();
    player->setColor(Color(0,255,0));
    player->setStartPos(Point(50,50));
    player->setKeyBinding(KEYBOARD_KEY_W, KEYBOARD_KEY_A,
                          KEYBOARD_KEY_S, KEYBOARD_KEY_D);
    player->buildPlayer();
    //player->setHitboxVisibility(true);

    // Obstacle 1
    obstacle1   = new GameObject();
    Controller *o1_controller = new Controller();
    obstacle1->setPos(100,100);
    Collider   *o1_collider = new Collider();
    o1_collider->addHitbox({Rect(PixelEngine::random(-10,10),PixelEngine::random(-10,10),PixelEngine::random(1,10),PixelEngine::random(1,10)),
                            Rect(PixelEngine::random(-10,10),PixelEngine::random(-10,10),PixelEngine::random(1,10),PixelEngine::random(1,10)),
                            Rect(PixelEngine::random(-10,10),PixelEngine::random(-10,10),PixelEngine::random(1,10),PixelEngine::random(1,10))});
    obstacle1->setCollider(o1_collider);
    obstacle1->addController(o1_controller);
    obstacle1->setHitboxVisibility(true);

    // Wall
    wall1 = new Wall();
    wall1->setDimension(PointU(1,50));
    wall1->setPos(Point(10,10));
    wall1->setColor(Color(142,50,1));
    wall1->addPixel({Pixel(Point(5,5),Color(255,0,0)),
                    Pixel(Point(6,6),Color(255,0,0)),
                    Pixel(Point(7,7),Color(255,0,0)),
                    Pixel(Point(8,8),Color(255,0,0))});

    imported = getimportedObject();
    imported->setHitboxVisibility(false);


    // Generate Ground
    ManagedGameObjectGroup *terainGroup = factory_terain(engine->getMapSize().getX()/16,5,Point(0,engine->getMapSize().getY()));


    // Make Boarder
    ManagedGameObjectGroup *boarderGroup = makeBoarder(engine);

    // Make water Block
    waterBlock = new GameObject();
    waterTexture = new AnimatedTexture();
    waterTexture->addTexture("..\\textures\\minecraft\\textures\\block\\water\\water_0.png");
    waterTexture->addTexture("..\\textures\\minecraft\\textures\\block\\water\\water_1.png");
    waterTexture->addTexture("..\\textures\\minecraft\\textures\\block\\water\\water_2.png");
    waterTexture->addTexture("..\\textures\\minecraft\\textures\\block\\water\\water_3.png");
    waterTexture->addTexture("..\\textures\\minecraft\\textures\\block\\water\\water_4.png");
    waterTexture->addTexture("..\\textures\\minecraft\\textures\\block\\water\\water_5.png");
    waterTexture->loadTexture();
   /* waterBlock->setTexture(waterTexture);
    waterBlock->loadTexture();
    waterBlock->setHitboxFromTexture();
    waterBlock->setTextureOnPainter();*/
    ManagedGameObjectGroup *waterGroup = new ManagedGameObjectGroup();

    Point offsetPos(30,30);
    for(int x=0; x<3; x++)
    {
        for(int y=0; y<3; y++)
        {
            GameObject *obj = new GameObject(*waterBlock);
            AnimatedTexture *texture = new AnimatedTexture(*waterTexture);
            obj->setPos(Vector(offsetPos) + Vector(Point(x*16,y*16)));
            obj->setTexture(texture);
            obj->setHitboxFromTexture();
            obj->setTextureOnPainter();

            waterTextureList.push_back(texture);
            waterGroup->add(obj);
        }
    }



    // Make Group of Objects for toggle Hitbox in loop below
    objectGroup = new ManagedGameObjectGroup();


    objectGroup->add(player);
    objectGroup->add(obstacle1);
    objectGroup->add(wall1);
    objectGroup->add(imported);
    objectGroup->add(waterGroup);
    objectGroup->add(boarderGroup);




    // Engine
    engine->setUserCheckEventLoop(userEventLoop);
    engine->setUserTickLoop(userTickLoop);
    engine->setUserDisplayLoop(userDisplayLoop);

    engine->addGroup(objectGroup);
    engine->addGroup(terainGroup);

    hitboxObjectList.add(objectGroup);
    hitboxObjectList.add(terainGroup);


    // Set Interactions
    engine->setCollisionMultiInteraction(player,imported);

    engine->setCollisionSingleInteraction({player,imported},{obstacle1});
    engine->setCollisionSingleInteraction({player,imported},boarderGroup);

    engine->setCollisionSingleInteraction({player,imported},terainGroup);
    // End Interactions

    // Set RenderLayer
    // engine->setRenderLayer_BOTTOM(background);
    engine->setRenderLayer_TOP(wall1);
    engine->setRenderLayer_BOTTOM(terainGroup);
    engine->setRenderLayer_BOTTOM(waterGroup);



    //Key Events
     keyEvent_P = new Event(KEYBOARD_KEY_P);
     keyEvent_O = new Event(KEYBOARD_KEY_O);
     keyEvent_H = new Event(KEYBOARD_KEY_H);
}
void clear_level()
{
    delete keyEvent_P;
    delete keyEvent_O;
    delete keyEvent_H;
}

void userEventLoop(double tickInterval,unsigned long long tick)
{
    keyEvent_P->checkEvent();
    keyEvent_O->checkEvent();
    keyEvent_H->checkEvent();

    if(keyEvent_P->isSinking())
    {
        //qDebug() << "keyEvent_P Sinking";
        engine->display_stats(!engine->display_stats(),Color(0,200,0),Point(10,20));
    }
    if(keyEvent_O->isPressed())
    {
        VectorF moving = imported->getMovingVector();
            if(moving.getLength() == 0)
                moving.setX(3);
            moving = VectorF::rotate(moving,(double)((rand() % 100)-50)/10);
            imported->move(moving);
    }

    if(keyEvent_H->isSinking())
    {
        hitboxIsVisible = !hitboxIsVisible;
        hitboxObjectList.setHitboxVisibility(hitboxIsVisible);
    }




}
void userTickLoop(double tickInterval,unsigned long long tick)
{


}
void userDisplayLoop(double frameInterval,unsigned long long tick)
{
    if(timer2.start(1))
    {
        toggle = !toggle;
       /* if(toggle)
            animatedTexture->select(1);
        else
            animatedTexture->select(0);*/

        animatedTexture->selectForward();

        obstacle1->setPos(200,100);
    }
    if(timer.start(0.2)/* && !toggle*/)
    {



       /* unsigned int currentWaterFrame = waterTexture->getSelected();
        if(currentWaterFrame == waterTexture->getTextureAmount()-1)
            currentWaterFrame = 0;
        else
            currentWaterFrame++;

        qDebug() << currentWaterFrame;
        waterTexture->selectForward();*/
        for(size_t i=0; i<waterTextureList.size(); i++)
        {
            waterTextureList[i]->selectForward();
        }

    }
    if(fadeTimer.start(0.05))
    {
        player->setColor(getRainbow(rad));
        rad += M_PI/10;
        if(rad >= 2*M_PI)
            rad -= 2*M_PI;
    }
}


GameObject *getimportedObject()
{
    //Timer timer;
    //timer.start(1000);
    GameObject *obj         = new GameObject();
    Collider   *collider    = new Collider();
    Painter    *painter     = new Painter();
    KeyController *controller = new KeyController();
    animatedTexture         = new AnimatedTexture();
    animatedTexture->addTexture("..\\textures\\minecraft\\textures\\block\\allium.png");
    //animatedTexture->addTexture("..\\textures\\minecraft\\textures\\block\\grass_block_side.png");
    animatedTexture->addTexture("..\\textures\\minecraft\\textures\\block\\allium_leaf.png");
    animatedTexture->addTexture("..\\textures\\minecraft\\textures\\block\\grass4.png");


    controller->setKey_forMove_UP(KEYBOARD_KEY_I);
    controller->setKey_forMove_LEFT(KEYBOARD_KEY_J);
    controller->setKey_forMove_DOWN(KEYBOARD_KEY_K);
    controller->setKey_forMove_RIGHT(KEYBOARD_KEY_L);
    controller->setStepSize(1);

    Property::Property property = obj->getProperty();
    property.setBody_weight(1);
    property.setBody_material(Property::Material::Grass);
    property.setType_description(Property::Description::dynamicObstacle);
    obj->setProperty(property);
    obj->setPos(70,50);

    obj->setPainter(painter);
    obj->setCollider(collider);
    obj->addController(controller);
    obj->setTexture(animatedTexture);
    //obj->setTexturePath("..\\textures\\minecraft\\textures\\block\\allium.png");
    obj->loadTexture();
    obj->setHitboxFromTexture();
    obj->setTextureOnPainter();
    //PixelEngine::loadFromImage("..\\textures\\minecraft\\textures\\block\\allium.png",collider,painter,ImageOrigin::bottomRightCorner);

    return obj;
}

Color getRainbow(double phase)
{
      int center = 128;
      int width = 127;
      double frequency = M_PI*2;
      Color color;
      color.r   = sin(frequency+2+phase) * width + center;
      color.g   = sin(frequency+0+phase) * width + center;
      color.b   = sin(frequency+4+phase) * width + center;
      return color;
}

ManagedGameObjectGroup *makeBoarder(PixelEngine *engine)
{
    PointU mapSize = engine->getMapSize();
    unsigned int boarderSize = 3;
    Color color(142,50,1);

    Wall *wall_1 = new Wall();
    wall_1->setDimension(PointU(boarderSize,mapSize.getY()+2*boarderSize));
    wall_1->setPos(Point(-boarderSize,-boarderSize));
    wall_1->setColor(color);

    Wall *wall_2 = new Wall();
    wall_2->setDimension(PointU(boarderSize,mapSize.getY()+2*boarderSize));
    wall_2->setPos(Point(mapSize.getX(),-boarderSize));
    wall_2->setColor(color);

    Wall *wall_3 = new Wall();
    wall_3->setDimension(PointU(mapSize.getX(),boarderSize));
    wall_3->setPos(Point(0,-boarderSize));
    wall_3->setColor(color);

    Wall *wall_4 = new Wall();
    wall_4->setDimension(PointU(mapSize.getX(),boarderSize));
    wall_4->setPos(Point(0,mapSize.getY()));
    wall_4->setColor(color);

    ManagedGameObjectGroup *group = new ManagedGameObjectGroup();;
    group->add(wall_1);
    group->add(wall_2);
    group->add(wall_3);
    group->add(wall_4);
    return group;
}
ManagedGameObjectGroup *factory_terain(const unsigned int &blocksX,const unsigned int &blocksY,const Point &bottomLeftOrigin)
{
    GameObject *grassBlock = new GameObject();
    Collider *collider = new Collider();
    Painter  *painter = new Painter();
    Controller *controller = new Controller();
   /* if(!PixelEngine::loadFromImage("..\\textures\\minecraft\\textures\\block\\grass_block_side.png",
                                   collider,painter,ImageOrigin::bottomLeftCorner))
        qDebug() << "can't load image";*/
    grassBlock->setCollider(collider);
    grassBlock->setPainter(painter);
    grassBlock->addController(controller);
    grassBlock->setPos(bottomLeftOrigin);
    grassBlock->setTexturePath("..\\textures\\minecraft\\textures\\block\\grass_block_side.png");
    grassBlock->loadTexture();


   /* Texture texture;
    texture.setFilePath("..\\textures\\minecraft\\textures\\block\\allium.png");
    texture.loadTexture();
    grassBlock->setHitboxFromTexture(texture);*/
    grassBlock->setHitboxFromTexture();
    grassBlock->setTextureOnPainter();

    Property::Property property = grassBlock->getProperty();
    property.setBody_weight(1);
    property.setBody_material(Property::Material::Grass);
    property.setType_description(Property::Description::staticObstacle);
    grassBlock->setProperty(property);


    Point blockSize(16,16);
    ManagedGameObjectGroup *group = new ManagedGameObjectGroup();
    for(size_t x=0; x<blocksX; x++)
    {
        for(size_t y=0; y<blocksY; y++)
        {
            GameObject *newBlock = new GameObject(*grassBlock);
            newBlock->setPos(bottomLeftOrigin.getX()+blockSize.getX()*x,bottomLeftOrigin.getY()-blockSize.getY()*y);
            group->add(newBlock);
            if(rand() % 5 == 0)
                y = blocksY;
        }
    }
    return group;
}
