#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ConfigUtil.h"
#include "Controller.h"

USING_NS_CC;

UILayer* GameScene::uiLayer = nullptr;
CameraNode* GameScene::CameraNode = nullptr;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	uiLayer = nullptr;
	CameraNode = nullptr;
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// ��ʼ����������
	if (!this->initWithPhysics())
	{
		return false;
	}

	// Set Physics Debug Mode
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// ��Ϸ�������ڵ�
	auto controller = Controller::create();
	// ��Ϸ���ڵ�
	CameraNode = CameraNode::create();
	CameraNode->setPosition(Vec2(ConfigUtil::visibleWidth / 2, ConfigUtil::visibleHeight / 2));
	CameraNode->setParent(this);
	// UI��
	uiLayer = UILayer::create();
	uiLayer->setParent(this);

	this->addChild(controller);
	this->addChild(CameraNode);
	this->addChild(uiLayer);

	// auto lable = Label::createWithTTF("Label", "fonts/Marker Felt.ttf", 32);
	// lable->setPosition(200, 200);
	// this->addChild(lable, 2);

	return true;
}

UILayer* GameScene::getUILayer()
{
	return this->uiLayer;
}

CameraNode* GameScene::getCameraLayer()
{
	return this->CameraNode;
}
