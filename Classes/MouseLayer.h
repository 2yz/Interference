#ifndef MOUSELAYER_H_
#define MOUSELAYER_H_

#include "cocos2d.h"

class MouseLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(MouseLayer);
	MouseLayer();
	virtual bool init() override;

protected:
	// Mouse
	cocos2d::Sprite* mouseSprite;
	// cocos2d::Vec2 boxPosition;
	virtual void update(float deltaTime) override;
};

#endif /* MOUSELAYER_H_ */