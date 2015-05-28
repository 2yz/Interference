#ifndef PLAYERLAYER_H_
#define PLAYERLAYER_H_

#include "cocos2d.h"

class PlayerLayer : public cocos2d::Layer{
public:
	PlayerLayer();
	virtual bool init() override;
	CREATE_FUNC(PlayerLayer);
	cocos2d::Sprite* getMyPlane();
	int getInitHP() const;

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 visibleOrigin;
	const int initHP;
	const float speed;
	float positionX;
	float positionY;
	bool moveUp;
	bool moveDown;
	bool moveLeft;
	bool moveRight;
	cocos2d::Sprite* mPlayer;
	// const cocos2d::Size winSize;
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;
	virtual void update(float delta) override;
};

#endif /* PLAYERLAYER_H_ */