/*
* 此类已弃用
*/

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
	float getPlayerPositionX();
	float getPlayerPositionY();
	// void setMoveUp(bool value);
	// void setMoveDown(bool value);
	// void setMoveLeft(bool value);
	// void setMoveRight(bool value);
private:
	const int initHP;
	const float acceleration;
	const float frictionCoefficient;
	const float maxSpeed;
	float speedX;
	float speedY;
	float playerPositionX;
	float playerPositionY;
	// bool moveUp;
	// bool moveDown;
	// bool moveLeft;
	// bool moveRight;
	cocos2d::Sprite* mPlayer;
	virtual void update(float deltaTime) override;
};

#endif /* PLAYERLAYER_H_ */