#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ConfigUtil.h"
#include "BasePlane.h"
#include "PlayerPlane.h"
#include "AnimationUtil.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	// auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
	// Set Physics Debug Mode
	// scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();
	layer->setPhyWorld(scene->getPhysicsWorld());

	// add layer as a child to scene
	scene->addChild(layer);

	auto layer2 = Layer::create();
	auto sp = Sprite::create();
	auto body = PhysicsBody::createBox(Size(100, 100));
	body->setVelocity(Vec2(random(-100, 100), random(-100, 100)));
	body->setGravityEnable(false);
	body->setCategoryBitmask(0x00000FFF);
	body->setCollisionBitmask(0x00000FFF);
	body->setContactTestBitmask(0x00000FFF);
	sp->setTag(4);
	sp->setPhysicsBody(body);
	sp->setPosition(Vec2(300,300));
	layer2->addChild(sp);
	scene->addChild(layer2);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Director::getInstance()->getOpenGLView()->setCursorVisible(true);

	// auto rootNode = CSLoader::createNode("MainScene.csb");
	// rootNode->getChildByName("")->

	// addChild(rootNode);

	auto edgeSp = Sprite::create();
	auto body = PhysicsBody::createEdgeBox(ConfigUtil::visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeSp->setPosition(Point(ConfigUtil::visibleSize.width / 2, ConfigUtil::visibleSize.height / 2));
	edgeSp->setPhysicsBody(body);
	addChild(edgeSp);
	edgeSp->setTag(0);

	auto listener = EventListenerMouse::create();
	listener->onMouseUp = CC_CALLBACK_1(HelloWorld::onMouseUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	// listener->onTouchEnded = [=](Touch* touch, Event* event){
	// 	auto location = touch->getLocation();
	// 	addNewSpriteAtPosition(location);
	// };



	// auto nothing = rootNode->getChildByName("nothing");
	// auto myScene = rootNode->getChildByName("Scene");
	// auto sprite = rootNode->getChildByName("Default");
	// auto button1 = rootNode->getChildByName("Button_1");
	// auto node1 = rootNode->getChildByName("Node_1");
	// auto button2 = rootNode->getChildByName("Button_2");
	// auto slider1 = rootNode->getChildByName("Node_1")->getChildByName("Slider_1");

	// 加载动画： 
	// ActionTimeline *action = CSLoader::createTimeline("MainScene.csb");
	// rootNode->runAction(action);
	// 注!!!：同一个文件创建的节点只能使用同一个文件创建的动画。 
	// 嵌套节点的动画会自动加载动画，可以用嵌套节点->getActionByTag(嵌套节点->getTag()) 来获取动画 

	// 播放动画： 
	// action->gotoFrameAndPlay(0, 60, true);//从第0帧到60帧循环播放。还有其他重载函数

	return true;
}

void HelloWorld::onEnter()
{
	Layer::onEnter();
	auto physicsListener = EventListenerPhysicsContact::create();
	physicsListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(physicsListener, this);
}

void HelloWorld::setPhyWorld(cocos2d::PhysicsWorld* world)
{
	m_world = world;
}

void HelloWorld::addNewSpriteAtPosition(cocos2d::Point p)
{
	auto test = PlayerPlane::create();
	test->setPosition(p);
        test->getPhysicsBody()->setGroup(random(-1,-2));
	test->getPhysicsBody()->setVelocity(Vec2(random(-200, 200), random(-200, 200)));
	test->getPhysicsBody()->setGravityEnable(false);
	test->getPhysicsBody()->setContactTestBitmask(0x00000FFF);

	int index = random(-2, -1);
	// int index = 1;
	test->getPhysicsBody()->setGroup(index);
	test->setTag(index);
	this->addChild(test);
}

void HelloWorld::onMouseUp(cocos2d::Event* event)
{
	EventMouse* e = (EventMouse*)event;
	auto location = Vec2(e->getCursorX(), e->getCursorY());
	addNewSpriteAtPosition(location);
}

bool HelloWorld::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto tag1 = static_cast<Node*>(contact.getShapeA()->getBody()->getNode())->getTag();
	auto tag2 = static_cast<Node*>(contact.getShapeB()->getBody()->getNode())->getTag();
	log("CONTACT TEST A: %d B: %d", tag1, tag2);
	return true;
}