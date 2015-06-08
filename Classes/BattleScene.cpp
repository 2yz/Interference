#include "BattleScene.h"
#include "cocostudio/CocoStudio.h"
#include "ConfigUtil.h"
#include "Controller.h"
#include "MouseLayer.h"

USING_NS_CC;

BattleScene* BattleScene::battleScene = nullptr;
UILayer* BattleScene::uiLayer = nullptr;
// CameraNode* BattleScene::cameraNode = nullptr;

BattleScene::BattleScene()
{
	battleScene = this;
}

BattleScene::~BattleScene()
{
	uiLayer = nullptr;
	battleScene = nullptr;
}

bool BattleScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// Init Physics World
	if (!this->initWithPhysics())
	{
		return false;
	}

	if (!this->initWithSize(ConfigUtil::visibleSize*2.5))
	{
		return false;
	}

	// Set Physics Debug Mode
	// this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Vec2(0.0f, 0.0f));

	// Game Controller Node
	auto controller = Controller::create();
	this->addChild(controller);

	// Battle Layer
	battleLayer = BattleLayer::create();
	this->addChild(battleLayer);

	// UI Layer
	uiLayer = UILayer::create();
	this->addChild(uiLayer);

	// Mouse Layer
	auto mouseLayer = MouseLayer::create();
	this->addChild(mouseLayer);

	return true;
}

UILayer* BattleScene::getUILayer()
{
	return this->uiLayer;
}

// CameraNode* BattleScene::getCameraLayer()
// {
// 	return this->cameraNode;
// }

void BattleScene::update(float deltaTime)
{
}