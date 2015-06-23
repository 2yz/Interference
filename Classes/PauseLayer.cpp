#include "PauseLayer.h"
#include "BattleScene.h"
#include "ConfigUtil.h"
#include "AudioEngine.h"

USING_NS_CC;

PauseLayer* PauseLayer::create(const std::string& label_text, const std::string& button_text)
{
	PauseLayer *pRet = new(std::nothrow) PauseLayer(label_text, button_text);
	CALL_INIT();
}

PauseLayer::PauseLayer(const std::string& label_text, const std::string& button_text) : PopupLayer(label_text, button_text)
{
}

bool PauseLayer::init()
{
	if (!PopupLayer::init())
		return false;
	// Keyboard Listener
	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(PauseLayer::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);
	return true;
}

void PauseLayer::buttonListener(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		experimental::AudioEngine::play2d(START_AUDIO, false, START_AUDIO_VOLUME);
		BattleScene::getInstance()->setBattleState(BattleState::BATTLE_ON);
		this->onDestroy();
		break;
	default:
		break;
	}
}

void PauseLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		this->onDestroy();
		break;
	default:
		break;
	}
}