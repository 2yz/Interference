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
protected:
	static bool move_up_;
	static bool move_down_;
	static bool move_left_;
	static bool move_right_;
	static bool mouse_down_;
	static bool key_e_pressed_;
	static bool key_e_released_;
	static cocos2d::Vec2 mouse_location_;
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onMouseDown(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event);
	void onMouseMove(cocos2d::Event* event);
};

#endif /* CONTROLLER_H_ */