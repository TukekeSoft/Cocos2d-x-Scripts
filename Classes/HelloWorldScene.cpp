#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vect(0, -500));
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
	
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	auto size = Director::getInstance()->getVisibleSize();
	auto origim = Director::getInstance()->getVisibleOrigin();

	//Creates a collision body in the edge of the screen, to prevent the sprite get out of the screen
	auto edgeBody = PhysicsBody::createEdgeBox(size, PHYSICSBODY_MATERIAL_DEFAULT, 1);

	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(size.width / 2 + origim.x, size.height / 2 + origim.y));
	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode);

	//Making the sprite
	auto whiteBox = Sprite::create("whiteBox.png");
	whiteBox->setPosition(Vec2(origim.x / 2, 200));
	
	auto whiteBoxBody = PhysicsBody::createBox(Size(whiteBox->getContentSize()), PhysicsMaterial(0, 0, 0));

	whiteBox->setPhysicsBody(whiteBoxBody);

	this->addChild(whiteBox);

	//Key events
	auto KeyListener = EventListenerKeyboard::create();
		
	KeyListener->onKeyPressed = [whiteBox](EventKeyboard::KeyCode keyCode, Event *event){
		//26 is the left key arrow , 27 is the right key arrow
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			whiteBox->getPhysicsBody()->setVelocity(Vect(-200, 0));
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			whiteBox->getPhysicsBody()->setVelocity(Vect(200, 0));
		}
	};

	KeyListener->onKeyReleased = [whiteBox](EventKeyboard::KeyCode keyCode, Event *event){
		//When the key is released it turns the velocity to 0, cancels the infinite movement of the sprite
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			whiteBox->getPhysicsBody()->setVelocity(Vect(0, 0));
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			whiteBox->getPhysicsBody()->setVelocity(Vect(0, 0));
		}
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(KeyListener, this);

    return true;
}
