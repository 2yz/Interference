#include "Controller.h"

USING_NS_CC;

bool Controller::moveUp = false;
bool Controller::moveDown = false;
bool Controller::moveLeft = false;
bool Controller::moveRight = false;
bool Controller::mouseDown = false;
cocos2d::Vec2 Controller::mouseLocation = Vec2();
bool Controller::keyEPressed = false;
bool Controller::keyEReleased = false;
// float Controller::cursorY = 0.0f;
// float Controller::cursorX = 0.0f;

Controller::~Controller()
{
	moveUp = false;
	moveDown = false;
	moveLeft = false;
	moveRight = false;
	mouseDown = false;
	mouseLocation = Vec2();
	// cursorX = 0.0f;
	// cursorY = 0.0f;
}

bool Controller::init()
{
	if (!Node::init())
	{
		return false;
	}

	// ¼àÌý¼üÅÌÊÂ¼þ
	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(Controller::onKeyPressed, this);
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2(Controller::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

	// Mouse Listener
	auto listenerMouse = EventListenerMouse::create();
	listenerMouse->onMouseDown = CC_CALLBACK_1(Controller::onMouseDown, this);
	listenerMouse->onMouseMove = CC_CALLBACK_1(Controller::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this);

	return true;
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

bool Controller::getMouseDown()
{
	return mouseDown;
}

bool Controller::getKeyEPressed()
{
	if (keyEPressed == true)
	{
		keyEPressed = false;
		return true;
	}
	return false;
}

bool Controller::getKeyEReleased()
{
	if (keyEReleased == true)
	{
		keyEReleased = false;
		return true;
	}
	return false;
}

cocos2d::Vec2& Controller::getMouseLocation()
{
	return mouseLocation;
}

// float Controller::getCursorX()
// {
// 	return cursorX;
// }
// 
// float Controller::getCursorY()
// {
// 	return cursorY;
// }

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
	case EventKeyboard::KeyCode::KEY_Q:
	case EventKeyboard::KeyCode::KEY_CAPITAL_Q:
		Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0.2f); break;
	case EventKeyboard::KeyCode::KEY_E:
	case EventKeyboard::KeyCode::KEY_CAPITAL_E:
		keyEPressed = true;
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
	case EventKeyboard::KeyCode::KEY_Q:
	case EventKeyboard::KeyCode::KEY_CAPITAL_Q:
		Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1.0f); break;
	case EventKeyboard::KeyCode::KEY_E:
	case EventKeyboard::KeyCode::KEY_CAPITAL_E:
		keyEReleased = false;
	default: break;
	}
}

void Controller::onMouseDown(cocos2d::Event* event)
{
	// auto e = static_cast<EventMouse*>(event);
	// log("# Down # X: %f ; Y: %f", e->getCursorX(), e->getCursorY());
	mouseLocation = static_cast<EventMouse*>(event)->getLocationInView();
	// cursorX = e->getCursorX();
	// cursorY = e->getCursorY();
}

void Controller::onMouseMove(cocos2d::Event* event)
{
	// auto e = static_cast<EventMouse*>(event);
	// log("# Move # X: %f ; Y: %f", e->getCursorX(), e->getCursorY());
	// cursorX = e->getCursorX();
	// cursorY = e->getCursorY();
	mouseLocation = static_cast<EventMouse*>(event)->getLocationInView();
	// log("# Mouse Location # X: %f Y: %f", mouseLocation.x, mouseLocation.y);
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