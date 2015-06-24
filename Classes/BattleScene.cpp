#include "BattleScene.h"
#include "cocostudio/CocoStudio.h"
#include "ConfigUtil.h"
#include "Controller.h"
#include "MouseLayer.h"
#include "PlayerUserData.h"
#include "ResultLayer.h"
#include "SimpleBattle.h"
#include "PauseLayer.h"
#include "AudioEngine.h"

USING_NS_CC;

BattleScene* BattleScene::battle_scene_ = nullptr;

BattleScene::BattleScene() : scene_state_(SceneState::NA), battle_state_(BattleState::NA), menu_layer_(nullptr), camera_node_(nullptr), hud_layer_(nullptr), battle_layer_(nullptr), result_layer_(nullptr), pause_layer_(nullptr)
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

	this->getPhysicsWorld()->setGravity(Vec2(0.0f, 0.0f));
	// Set Physics Debug Mode
	// this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// Game Controller Node
	auto controller = Controller::create();
	this->addChild(controller, 0);
	// Mouse Layer
	auto mouseLayer = MouseLayer::create();
	this->addChild(mouseLayer, 20);

	// Keyboard Listener
	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(BattleScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

	setListener();
	setSceneState(SceneState::INITIAL);
	setSceneState(SceneState::MENU);
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
		switch (*buf)
		{
		case BATTLE_EVENT_WIN:
			if (scene_state_ == SceneState::BATTLE)
				setBattleState(BattleState::BATTLE_RESULT_WIN);
			break;
		case BATTLE_EVENT_LOSE:
			if (scene_state_ == SceneState::BATTLE)
				setBattleState(BattleState::BATTLE_RESULT_LOSS);
			break;
		default: break;
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

void BattleScene::setSceneState(SceneState scene_state)
{
	if (scene_state_ == scene_state)
		return;
	exitSceneState();
	enterSceneState(scene_state);
}

void BattleScene::enterSceneState(SceneState scene_state)
{
	scene_state_ = scene_state;
	switch (scene_state)
	{
	case SceneState::INITIAL:
		camera_node_ = CameraManager::create();
		this->addChild(camera_node_, 1);
		camera_node_->addBackgroundManager(BackgroundManager::create());
		break;
	case SceneState::MENU:
		camera_node_->setCameraPosition((config::kBattleScene - config::visible_size) / 2);
		menu_layer_ = MenuLayer::create();
		this->addChild(menu_layer_, 3);
		break;
	case SceneState::BATTLE:
		// UI Layer
		hud_layer_ = HUDLayer::create();
		this->addChild(hud_layer_, 2);
		// Battle Layer 
		battle_layer_ = SimpleBattle::create();
		camera_node_->addBattleManager(battle_layer_);
		setBattleState(BattleState::BATTLE_ON);
		break;
	case SceneState::EXIT:
		this->runAction(Sequence::create(DelayTime::create(0.7f), CallFuncN::create([&](Node* sender){ Director::getInstance()->end(); }), nullptr));
		break;
	default: break;
	}
}

void BattleScene::exitSceneState()
{
	switch (scene_state_)
	{
	case SceneState::MENU:
		menu_layer_->onDestroy();
		menu_layer_ = nullptr;
		break;
	case SceneState::BATTLE:
		setBattleState(BattleState::NA);
		if (hud_layer_ != nullptr)
		{
			this->removeChild(hud_layer_);
			hud_layer_ = nullptr;
		}
		if (battle_layer_ != nullptr)
		{
			camera_node_->removeBattleManager();
			battle_layer_ = nullptr;
		}
		break;
	default: break;
	}
	scene_state_ = SceneState::NA;
}

void BattleScene::setBattleState(BattleState battle_state)
{
	if (scene_state_ != SceneState::BATTLE)
		return;
	if (battle_state_ == battle_state)
		return;
	exitBattleState();
	enterBattleState(battle_state);
}

void BattleScene::enterBattleState(BattleState battle_state)
{
	battle_state_ = battle_state;
	switch (battle_state)
	{
	case BattleState::BATTLE_PAUSE:
		battle_layer_->pauseLayer();
		pause_layer_ = PauseLayer::create("GAME PAUSED", "RESUME");
		this->addChild(pause_layer_, 10);
		break;
	case BattleState::BATTLE_RESULT_WIN:
		result_layer_ = ResultLayer::create("YOU WIN", "BACK");
		this->addChild(result_layer_, 10);
		break;
	case BattleState::BATTLE_RESULT_LOSS:
		result_layer_ = ResultLayer::create("YOU LOSE", "BACK");
		this->addChild(result_layer_, 10);
		break;
	default: break;
	}
}

void BattleScene::exitBattleState()
{
	switch (battle_state_)
	{
	case BattleState::BATTLE_PAUSE:
		battle_layer_->resumeLayer();
		pause_layer_->onDestroy();
		pause_layer_ = nullptr;
		break;
	case BattleState::BATTLE_RESULT_WIN:
	case BattleState::BATTLE_RESULT_LOSS:
		result_layer_->onDestroy();
		result_layer_ = nullptr;
		break;
	default: break;
	}
	battle_state_ = BattleState::NA;
}

void BattleScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		if (scene_state_ == SceneState::BATTLE && battle_state_ == BattleState::BATTLE_ON)
		{
			experimental::AudioEngine::play2d(END_AUDIO, false, END_AUDIO_VOLUME);
			setBattleState(BattleState::BATTLE_PAUSE);
		}
		else if (scene_state_ == SceneState::BATTLE && battle_state_ == BattleState::BATTLE_PAUSE)
		{
			experimental::AudioEngine::play2d(START_AUDIO, false, START_AUDIO_VOLUME);
			setBattleState(BattleState::BATTLE_ON);
		}
		break;
	case EventKeyboard::KeyCode::KEY_BACKSPACE:
		if (scene_state_ == SceneState::BATTLE)
		{
			experimental::AudioEngine::play2d(END_AUDIO, false, END_AUDIO_VOLUME);
			setSceneState(SceneState::MENU);
		}
	default: break;
	}
}
