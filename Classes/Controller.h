#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "cocos2d.h"

class Controller : public cocos2d::Node
{
public:
	virtual ~Controller();
	virtual bool init() override;
	CREATE_FUNC(Controller);
	static bool getMoveUp();
	static bool getMoveDown();
	static bool getMoveLeft();
	static bool getMoveRight();
	static bool getMouseDown();
	static bool getKeyEPressed();
	static bool getKeyEReleased();
	static cocos2d::Vec2& getMouseLocation();
	// static float getCursorX();
	// static float getCursorY();
	// static void setMoveUp(bool value);
	// static void setMoveDown(bool value);
	// static void setMoveLeft(bool value);
	// static void setMoveRight(bool value);
protected:
	static bool moveUp;
	static bool moveDown;
	static bool moveLeft;
	static bool moveRight;
	static bool mouseDown;
	static bool keyEPressed;
	static bool keyEReleased;
	static cocos2d::Vec2 mouseLocation;
	// static float cursorX;
	// static float cursorY;
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onMouseDown(cocos2d::Event* event);
	void onMouseMove(cocos2d::Event* event);
};

#endif /* CONTROLLER_H_ */