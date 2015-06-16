#include "BattleScene.h"
#include "cocostudio/CocoStudio.h"
#include "ConfigUtil.h"
#include "Controller.h"
#include "MouseLayer.h"

USING_NS_CC;

BattleScene* BattleScene::battleScene = nullptr;
// CameraNode* BattleScene::cameraNode = nullptr;

BattleScene::BattleScene() : _HUDLayer(nullptr)
{
	battleScene = this;
}

BattleScene::~BattleScene()
{
	_HUDLayer = nullptr;
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

	if (!this->initWithSize(config::visible_size*2.5))
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
	_HUDLayer = HUDLayer::create();
	this->addChild(_HUDLayer);

	// Mouse Layer
	auto mouseLayer = MouseLayer::create();
	this->addChild(mouseLayer);

	// Add BackgroundMusic
	// CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Title.mp3", true);
	// CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.8f);

	return true;
}

HUDLayer* BattleScene::getHUDLayer()
{
	return this->_HUDLayer;
}

// CameraNode* BattleScene::getCameraLayer()
// {
// 	return this->cameraNode;
// }

void BattleScene::update(float deltaTime)
{
}