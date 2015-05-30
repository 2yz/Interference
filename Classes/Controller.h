#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "cocos2d.h"

class Controller : public cocos2d::Node
{
public:
	virtual ~Controller();
	virtual bool init() override;
	CREATE_FUNC(Controller);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	static bool getMoveUp();
	static bool getMoveDown();
	static bool getMoveLeft();
	static bool getMoveRight();
	// static void setMoveUp(bool value);
	// static void setMoveDown(bool value);
	// static void setMoveLeft(bool value);
	// static void setMoveRight(bool value);
private:
	static bool moveUp;
	static bool moveDown;
	static bool moveLeft;
	static bool moveRight;
};

#endif /* CONTROLLER_H_ */