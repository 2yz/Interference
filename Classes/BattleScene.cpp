#include "BattleScene.h"
#include "cocostudio/CocoStudio.h"
#include "ConfigUtil.h"
#include "Controller.h"
#include "MouseLayer.h"
#include "PlayerUserData.h"
#include "ResultLayer.h"

USING_NS_CC;

BattleScene* BattleScene::battle_scene_ = nullptr;

BattleScene::BattleScene() : battle_scene_state_(MENU), camera_node_(nullptr), hud_layer_(nullptr), battle_layer_(nullptr)
{
	battle_scene_ = this;
}

BattleScene::~BattleScene()
{
	battle_scene_ = nullptr;
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
	this->addChild(controller, 0);
	// Mouse Layer
	auto mouseLayer = MouseLayer::create();
	this->addChild(mouseLayer, 4);
	// Menu Layer
	auto menu_layer_ = MenuLayer::create();
	this->addChild(menu_layer_, 3);

	camera_node_ = CameraNode::create();
	this->addChild(camera_node_, 1);

	// Keyboard Listener
	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(BattleScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);
	
	setListener();

	return true;
}

void BattleScene::onEnter()
{
	Scene::onEnter();
}

void BattleScene::setListener()
{
	auto player_listener = EventListenerCustom::create(BATTLE_EVENT, [=](EventCustom* event)
	{
		auto buf = static_cast<int*>(event->getUserData());
		if (*buf == BATTLE_EVENT_LOSE)
		{
			auto result_layer = ResultLayer::create("YOU LOSE", "BACK");
			this->addChild(result_layer);
		}
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(player_listener, this);
}

BattleScene* BattleScene::getInstance()
{
	return battle_scene_;
}

HUDLayer* BattleScene::getHUDLayer()
{
	return this->hud_layer_;
}

void BattleScene::openMenu()
{
	auto menu_layer_ = MenuLayer::create();
	this->addChild(menu_layer_, 3);
	if (hud_layer_ != nullptr)
	{
		this->removeChild(hud_layer_, true);
		hud_layer_ = nullptr;
	}
	if (battle_layer_!= nullptr)
	{
		camera_node_->removeChild(battle_layer_, true);
		battle_layer_ = nullptr;
	}
	battle_scene_state_ = MENU;
}

void BattleScene::startBattle()
{
	// UI Layer
	hud_layer_ = HUDLayer::create();
	this->addChild(hud_layer_, 2);
	// Battle Layer 
	battle_layer_ = BattleLayer::create();
	camera_node_->addChild(battle_layer_, 1);
	battle_scene_state_ = BATTLE;
}

void BattleScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		if (battle_layer_ != nullptr && (battle_scene_state_ == BATTLE || battle_scene_state_ == BATTLE_PAUSE))
		{
			if (battle_layer_->isPaused())
			{
				battle_layer_->resumeLayer();
				battle_scene_state_ = BATTLE;
			}
			else
			{
				battle_layer_->pauseLayer();
				battle_scene_state_ = BATTLE_PAUSE;
			}
		}
		break;
	case EventKeyboard::KeyCode::KEY_BACKSPACE:
		if (battle_scene_state_ == BATTLE)
			openMenu();
	default:
		break;
	}
}
