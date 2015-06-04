#include "BattleScene.h"
#include "cocostudio/CocoStudio.h"
#include "ConfigUtil.h"
#include "Controller.h"

USING_NS_CC;

BattleScene* BattleScene::battleScene = nullptr;
UILayer* BattleScene::uiLayer = nullptr;
CameraNode* BattleScene::cameraNode = nullptr;

BattleScene::BattleScene()
{
	battleScene = this;
}

BattleScene::~BattleScene()
{
	uiLayer = nullptr;
	cameraNode = nullptr;
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
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Vec2(0.0f, 0.0f));

	// 游戏控制器节点
	auto controller = Controller::create();
	// 游戏主节点
	cameraNode = CameraNode::create();
	cameraNode->setPosition(Vec2(ConfigUtil::visibleWidth / 2, ConfigUtil::visibleHeight / 2));
	cameraNode->setParent(this);
	
	// UI层
	uiLayer = UILayer::create();
	uiLayer->setParent(this);

	this->addChild(controller);
	this->addChild(cameraNode);
	this->addChild(uiLayer);

	// auto lable = Label::createWithTTF("Label", "fonts/Marker Felt.ttf", 32);
	// lable->setPosition(200, 200);
	// this->addChild(lable, 2);

	// _camera = Camera::createOrthographic(ConfigUtil::visibleWidth, ConfigUtil::visibleHeight, 1.0f, 1000.0f);

	return true;
}

UILayer* BattleScene::getUILayer()
{
	return this->uiLayer;
}

CameraNode* BattleScene::getCameraLayer()
{
	return this->cameraNode;
}

void BattleScene::update(float deltaTime)
{
	
}