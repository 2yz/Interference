#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ConfigUtil.h"
#include "Controller.h"

USING_NS_CC;

UILayer* GameScene::uiLayer = nullptr;
ControlNode* GameScene::controlNode = nullptr;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	uiLayer = nullptr;
	controlNode = nullptr;
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// 初始化物理世界
	if (!this->initWithPhysics())
	{
		return false;
	}

	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto controller = Controller::create();
	
	controlNode = ControlNode::create();
	controlNode->setPosition(Vec2(ConfigUtil::visibleWidth / 2, ConfigUtil::visibleHeight / 2));
	controlNode->setParent(this);

	uiLayer = UILayer::create();
	uiLayer->setParent(this);

	// this->addChild(gameBackgroundLayer, 1);

	this->addChild(controller);
	this->addChild(controlNode);
	this->addChild(uiLayer);
	// this->addChild(bulletLayer, 3);
	// this->addChild(playerLayer, 2);
	// this->addChild(enemyBulletLayer, 3);
	// this->addChild(enemyLayer, 2);

	// auto lable = Label::createWithTTF("Label", "fonts/Marker Felt.ttf", 32);
	// lable->setPosition(200, 200);
	// this->addChild(lable, 2);

	// TODO 修改Listener位置
	// auto listener = EventListenerMouse::create();
	// listener->onMouseDown = CC_CALLBACK_1(GameScene::mouseDown, this);
	// listener->onMouseMove = CC_CALLBACK_1(GameScene::mouseMove, this);
	// _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

// EnemyBulletLayer* GameScene::getEnemyBulletLayer()
// {
// 	return this->enemyBulletLayer;
// }
// 
// EnemyLayer* GameScene::getEnemyLayer()
// {
// 	return this->enemyLayer;
// }

UILayer* GameScene::getUILayer()
{
	return this->uiLayer;
}

ControlNode* GameScene::getCameraLayer()
{
	return this->controlNode;
}

// BulletLayer* GameScene::getBulletLayer()
// {
// 	return this->bulletLayer;
// }
// 
// PlayerLayer* GameScene::getPlayerLayer()
// {
// 	return this->playerLayer;
// }

void GameScene::mouseDown(cocos2d::Event* event)
{
	auto e = static_cast<EventMouse*>(event);
	log("#DOWN# X: %f ; Y: %f", e->getCursorX(), e->getCursorY());
	auto x = e->getCursorX();
	auto y = e->getCursorY();
}

void GameScene::mouseMove(cocos2d::Event* event)
{
	auto e = static_cast<EventMouse*>(event);
	log("#MOVE# X: %f ; Y: %f", e->getCursorX(), e->getCursorY());
	auto x = e->getCursorX();
	auto y = e->getCursorY();
}