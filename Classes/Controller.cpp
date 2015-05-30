#include "Controller.h"

USING_NS_CC;

bool Controller::moveUp = false;
bool Controller::moveDown = false;
bool Controller::moveLeft = false;
bool Controller::moveRight = false;


Controller::~Controller()
{
	moveUp = false;
	moveDown = false;
	moveLeft = false;
	moveRight = false;
}

bool Controller::init()
{
	if (!Node::init())
	{
		return false;
	}

	// ¼àÌý¼üÅÌÊÂ¼þ
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Controller::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Controller::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void Controller::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
	case EventKeyboard::KeyCode::KEY_CAPITAL_W:
		moveUp = true; break;
	case EventKeyboard::KeyCode::KEY_S:
	case EventKeyboard::KeyCode::KEY_CAPITAL_S:
		moveDown = true; break;
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_CAPITAL_A:
		moveLeft = true; break;
	case EventKeyboard::KeyCode::KEY_D:
	case EventKeyboard::KeyCode::KEY_CAPITAL_D:
		moveRight = true; break;
	default: break;
	}
}

void Controller::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
	case EventKeyboard::KeyCode::KEY_CAPITAL_W:
		moveUp = false; break;
	case EventKeyboard::KeyCode::KEY_S:
	case EventKeyboard::KeyCode::KEY_CAPITAL_S:
		moveDown = false; break;
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_CAPITAL_A:
		moveLeft = false; break;
	case EventKeyboard::KeyCode::KEY_D:
	case EventKeyboard::KeyCode::KEY_CAPITAL_D:
		moveRight = false; break;
	default: break;
	}
}

bool Controller::getMoveUp()
{
	return moveUp;
}

bool Controller::getMoveDown()
{
	return moveDown;
}

bool Controller::getMoveLeft()
{
	return moveLeft;
}

bool Controller::getMoveRight()
{
	return moveRight;
}

// void Controller::setMoveUp(bool value)
// {
// 	moveUp = value;
// }
// 
// void Controller::setMoveDown(bool value)
// {
// 	moveDown = value;
// }
// 
// void Controller::setMoveLeft(bool value)
// {
// 	moveLeft = value;
// }
// 
// void Controller::setMoveRight(bool value)
// {
// 	moveRight = value;
// }