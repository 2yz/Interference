#include "Controller.h"

USING_NS_CC;

bool Controller::move_up_ = false;
bool Controller::move_down_ = false;
bool Controller::move_left_ = false;
bool Controller::move_right_ = false;
bool Controller::mouse_down_ = false;
cocos2d::Vec2 Controller::mouse_location_ = Vec2();
bool Controller::key_e_pressed_ = false;
bool Controller::key_e_released_ = false;

Controller::~Controller()
{
	move_up_ = false;
	move_down_ = false;
	move_left_ = false;
	move_right_ = false;
	mouse_down_ = false;
	mouse_location_ = Vec2();
}

bool Controller::init()
{
	if (!Node::init())
	{
		return false;
	}

	// Keyboard Listener
	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(Controller::onKeyPressed, this);
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2(Controller::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

	// Mouse Listener
	auto listenerMouse = EventListenerMouse::create();
	listenerMouse->onMouseDown = CC_CALLBACK_1(Controller::onMouseDown, this);
	listenerMouse->onMouseUp = CC_CALLBACK_1(Controller::onMouseUp, this);
	listenerMouse->onMouseMove = CC_CALLBACK_1(Controller::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this);

	return true;
}

bool Controller::getMoveUp()
{
	return move_up_;
}

bool Controller::getMoveDown()
{
	return move_down_;
}

bool Controller::getMoveLeft()
{
	return move_left_;
}

bool Controller::getMoveRight()
{
	return move_right_;
}

bool Controller::getMouseDown()
{
	return mouse_down_;
}

bool Controller::getKeyEPressed()
{
	if (key_e_pressed_ == true)
	{
		key_e_pressed_ = false;
		return true;
	}
	return false;
}

bool Controller::getKeyEReleased()
{
	if (key_e_released_ == true)
	{
		key_e_released_ = false;
		return true;
	}
	return false;
}

cocos2d::Vec2& Controller::getMouseLocation()
{
	return mouse_location_;
}

void Controller::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
	case EventKeyboard::KeyCode::KEY_CAPITAL_W:
		move_up_ = true; break;
	case EventKeyboard::KeyCode::KEY_S:
	case EventKeyboard::KeyCode::KEY_CAPITAL_S:
		move_down_ = true; break;
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_CAPITAL_A:
		move_left_ = true; break;
	case EventKeyboard::KeyCode::KEY_D:
	case EventKeyboard::KeyCode::KEY_CAPITAL_D:
		move_right_ = true; break;
	case EventKeyboard::KeyCode::KEY_E:
	case EventKeyboard::KeyCode::KEY_CAPITAL_E:
		key_e_pressed_ = true; break;
	}
}

void Controller::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
	case EventKeyboard::KeyCode::KEY_CAPITAL_W:
		move_up_ = false; break;
	case EventKeyboard::KeyCode::KEY_S:
	case EventKeyboard::KeyCode::KEY_CAPITAL_S:
		move_down_ = false; break;
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_CAPITAL_A:
		move_left_ = false; break;
	case EventKeyboard::KeyCode::KEY_D:
	case EventKeyboard::KeyCode::KEY_CAPITAL_D:
		move_right_ = false; break;
	case EventKeyboard::KeyCode::KEY_E:
	case EventKeyboard::KeyCode::KEY_CAPITAL_E:
		key_e_released_ = false;
	default: break;
	}
}

void Controller::onMouseDown(cocos2d::Event* event)
{
	auto e = static_cast<EventMouse*>(event);
	mouse_down_ = true;
	mouse_location_ = static_cast<EventMouse*>(event)->getLocationInView();
}

void Controller::onMouseUp(cocos2d::Event* event)
{
	mouse_down_ = false;
	mouse_location_ = static_cast<EventMouse*>(event)->getLocationInView();
}

void Controller::onMouseMove(cocos2d::Event* event)
{
	auto e = static_cast<EventMouse*>(event);
	mouse_location_ = static_cast<EventMouse*>(event)->getLocationInView();
}
