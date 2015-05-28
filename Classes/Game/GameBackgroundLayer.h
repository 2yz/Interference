#ifndef GAMEBACKGROUNDLAYER_H_
#define GAMEBACKGROUNDLAYER_H_

#include "cocos2d.h"

class GameBackgroundLayer : public cocos2d::Layer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init() override;

	// implement the "static create()" method manually
	CREATE_FUNC(GameBackgroundLayer);
	void updateOnce(float dt);
private:
	cocos2d::Sprite* background1;
	cocos2d::Sprite* background2;
	// cocos2d::Size visibleSize;
	void update(float useless) override;
};

#endif /* GAMEBACKGROUNDLAYER_H_ */