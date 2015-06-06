#include "BattleScene.h"
#include "cocostudio/CocoStudio.h"
#include "ConfigUtil.h"
#include "Controller.h"

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
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Vec2(0.0f, 0.0f));


	// ��Ϸ�������ڵ�
	auto controller = Controller::create();
	this->addChild(controller);

	// ��Ϸ���ڵ�
	// cameraNode = CameraNode::create();
	// cameraNode->setPosition(Vec2(ConfigUtil::visibleWidth / 2, ConfigUtil::visibleHeight / 2));
	// cameraNode->setParent(this);
	// this->addChild(cameraNode);

	// Battle Layer
	battleLayer = BattleLayer::create();
	battleLayer->setParent(this);
	this->addChild(battleLayer);

	// UI Layer
	uiLayer = UILayer::create();
	uiLayer->setParent(this);
	this->addChild(uiLayer);

	// auto lable = Label::createWithTTF("Label", "fonts/Marker Felt.ttf", 32);
	// lable->setPosition(200, 200);
	// this->addChild(lable, 2);

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